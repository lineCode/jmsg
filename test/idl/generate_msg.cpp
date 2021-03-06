#include "parser.hpp"

static std::size_t s_msg_num = 0;
static const char * const s_mid_under_type = "uint16_t";

static void gen_msg_enum(const std::size_t lvl)
{
	s_outf_id.pf(lvl, "enum class mid_t : %s {\n", s_mid_under_type);
	s_outf_id.pf(lvl+1, "nil = 0,	/// occupy symbol, correspond to \\em NULL.\n");

	std::size_t i = 0;
	for (const auto & itr : s_msg_lists) {
		++i;
		s_outf_id.pf(lvl+1, "%s = %d,\n", itr.first.c_str(), (int)i);
	}
	s_msg_num = i + 1;

	s_outf_id.pf(lvl, "};\n");
}

static void gen_msg_map(const std::size_t lvl)
{
	s_outf_id.pf(lvl, "template<mid_t mid>\n");
	s_outf_id.pf(lvl, "struct msg_helper final {};\n\n");
	for (const auto & itr: s_msg_lists) {
		const char * evt_name = itr.first.c_str();
		const rapidjson::Value & val = *(itr.second);
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_id.pf(lvl, "template<>\n");
		s_outf_id.pf(lvl, "struct msg_helper<mid_t::%s> final {\n", evt_name);
		s_outf_id.pf(lvl+1, "typedef struct %s value_type;\n", type_name);
		s_outf_id.pf(lvl, "};\n\n");
	}

}

static void gen_msg_glb(const std::size_t lvl)
{
	s_outf_converter.pf(lvl, "/// mid to string\n");
	s_outf_converter.pf(lvl, "static rapidjson::Value::StringRefType const s_mid_to_str[] = {\n");
	s_outf_converter.pf(lvl+1, "\"nil\",\n");
	for (const auto & itr: s_msg_lists) {
		const char * evt_name = itr.first.c_str();
		s_outf_converter.pf(lvl+1, "\"%s\",\n", evt_name);
	}
	s_outf_converter.pf(lvl, "};\n\n");

	s_outf_converter.pf(lvl, "static rapidjson::Value::StringRefType const s_id = \"id\";\n");
	s_outf_converter.pf(lvl, "static rapidjson::Value::StringRefType const s_data = \"data\";\n");
}

static void generate_msg_sender_header(std::size_t lvl)
{
	s_outf_sender.pf(lvl, R"senderheader(
/// @class sender : used to send messages
class sender final {
public:
	sender();
	~sender();
public:
	template<mid_t mid, typename _T >
	void fill_to(typename msg_helper<mid>::value_type const & msg,  _T & o, size_t (_T::*f)(const void *, size_t))
	{
		__reset(mid);
		__pack(msg);
		__serialize();
		__fill_header();
		o.f(m_buf, __size());
	}

	template< mid_t mid >
	void fill_to(typename msg_helper<mid>::value_type const & msg, std::function<size_t(const void *, size_t)>  f)
	{
		__reset(mid);
		__pack(msg);
		__serialize();
		__fill_header();
		f(m_buf, __size());
	}
private:
)senderheader");

	for (const auto & itr: s_msg_order) {
		/// @todo maybe not struct
		const rapidjson::Value & val = *itr;
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_sender.pf(lvl+1, "void __pack(const struct %s & val);\n", type_name);
	}

	s_outf_sender.pf(lvl, R"senderheader(
private:
	void __reset(mid_t mid);
	void __serialize();
private:
	std::size_t __size() const
	{
		return (m_pcur - m_buf);
	}
private:
	void __fill_header();
private:
	uint8_t m_buf[65536];
	uint8_t * m_pcur;
	const uint8_t * const m_pend;
	void * m_doc;
};

)senderheader");

	s_outf_sender.pf(lvl, "\n");
}

static void generate_msg_sender_implement(std::size_t lvl)
{
	s_outf_converter.pf(lvl, R"senderfillheader(
/// @sender constructor
sender::sender()
: m_pcur(m_buf)
, m_pend(m_buf + sizeof(m_buf))
, m_doc(new rapidjson::Document())
{}

/// @sender destructor
sender::~sender()
{
	delete (rapidjson::Document*)m_doc;
}

/// @sender reset
void sender::__reset(mid_t mid)
{
	m_pcur = m_buf + msg_header_size;
	((rapidjson::Document*)m_doc)->SetObject();

	rapidjson::Document & doc = *(rapidjson::Document *)m_doc;
	doc.AddMember(s_id, s_mid_to_str[(%s)mid], doc.GetAllocator());
}

/// @sender serialize
void sender::__serialize()
{
	out_wrapper buf((char *)m_pcur);
	rapidjson::Writer<out_wrapper> writer(buf);
	((rapidjson::Document *)m_doc)->Accept(writer);
	m_pcur = (uint8_t *)buf.pcur;
}

/// @sender::__fill_header
void sender::__fill_header(void)
{
	std::size_t len = __size();
	m_buf[0] = 0;
	m_buf[1] = 0;
	m_buf[2] = 'F';
	m_buf[3] = 'S';
	m_buf[5] = (len & 0xFF); len >>= 8;
	m_buf[4] = (len & 0xFF);
	m_buf[6] = 0;
	m_buf[7] = 0;
}

)senderfillheader", s_mid_under_type);
	s_outf_converter.pf(lvl, "\n");

	s_outf_converter.pf(lvl, "/// messages packer wrapper\n");
	for (const auto & itr: s_msg_order) {
		/// @todo maybe not struct
		const rapidjson::Value & val = *itr;
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_converter.pf(lvl, "void sender::__pack(const struct %s & val)\n", type_name);
		s_outf_converter.pf(lvl, "{\n");
		s_outf_converter.pf(lvl+1, "rapidjson::Document & doc = *(rapidjson::Document *)m_doc;\n");
		s_outf_converter.pf(lvl+1, "doc.AddMember(s_data, c2json(doc, val), doc.GetAllocator());\n");
		s_outf_converter.pf(lvl, "}\n\n");
	}
}

static void generate_msg_rcver_header(std::size_t lvl)
{
	s_outf_rcver.pf(lvl, R"rcverheader(
/// @class rcver : used to receive messages
class rcver final {
public:
	rcver();
	~rcver();
public:
	void fill_from(std::function<size_t (void *, size_t)> f);

	template<mid_t mid, template<mid_t> class T>
	void register_callback(std::function<void(T<mid> &)> cb)
	{
		m_cbs[__mid_to_str(mid)] = [this, cb](void) -> void {
			T<mid> tmp;
			__unpack((typename msg_helper<mid>::value_type &)tmp);
			cb(tmp);
		};
	}

	template<mid_t mid>
	void register_callback(std::function<void(typename msg_helper<mid>::value_type &)> cb)
	{
		m_cbs[__mid_to_str(mid)] = [this, cb](void) -> void {
			typename msg_helper<mid>::value_type msg;
			__unpack(msg);
			cb(msg);
		};
	}
private:
	const char * __mid_to_str(mid_t mid);
)rcverheader");

	for (const auto & itr: s_msg_order) {
		rapidjson::Value & val = *itr;
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_rcver.pf(lvl+1, "void __unpack(struct %s & dst);\n", type_name);
	}

	s_outf_rcver.pf(lvl, R"rcverheader(
private:
	void __reset();
private:
	uint8_t m_buf[65536];
	std::size_t m_size;
	const uint8_t * const m_pend;
	void * m_doc;
	std::map<std::string, std::function<void(void)>> m_cbs;
};

)rcverheader");
#if 0
	for (const auto & itr: s_msg_lists) {
		const char * evt_name = itr.first.c_str();
		const rapidjson::Value & val = *(itr.second);
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_rcver.pf(lvl, "template<> void rcver::register_callback<mid_t::%s>(std::function< void(std::function<void(struct %s&)>)> f);\n", evt_name, type_name);
	}
#endif

	s_outf_rcver.pf(lvl, "\n");
}

static void generate_msg_rcver_implement(std::size_t lvl)
{
	s_outf_converter.pf(lvl, R"rcverimplementer(
/// @class rcver : used to receive messages
rcver::rcver()
: m_size(0)
, m_pend(m_buf + sizeof(m_buf))
, m_doc(new rapidjson::Document())
{}

rcver::~rcver()
{
	delete (rapidjson::Document*)m_doc;
}

void rcver::__reset()
{
	m_size = 0;
	((rapidjson::Document*)m_doc)->SetNull();
}

void rcver::fill_from(std::function<size_t (void *, size_t)> f)
{
	if (m_size < msg_header_size) {
		m_size += f(&m_buf[m_size], msg_header_size - m_size);
		if (m_size < msg_header_size) {
			return;
		}
	}

	/// check header
	if (false) {
		__reset();
		while (f(m_buf, sizeof(m_buf)) > 0) {}
		return;
	}

	std::size_t len = (((std::size_t)m_buf[4]) << 8) | m_buf[5];
	if (sizeof(m_buf) <= len) {
		__reset();
		while (f(m_buf, sizeof(m_buf)) > 0) {}
		return;
	}

	if (m_size < len) {
		m_size += f(&m_buf[m_size], len - m_size);
		if (m_size < len) {
			return;
		}
	}

	m_buf[m_size] = '\0';

	/// process
	rapidjson::Document & doc = *((rapidjson::Document*)m_doc);
	doc.ParseInsitu((char *)&m_buf[msg_header_size]);
	auto & cb = m_cbs[doc.FindMember(s_id)->value.GetString()];
	if (cb) { cb(); }

	__reset();
}

)rcverimplementer");

#if 0
	/// register callback
	s_outf_converter.pf(lvl, "/// messages register\n");
	for (const auto & itr: s_msg_lists) {
		const char * evt_name = itr.first.c_str();
		const rapidjson::Value & val = *(itr.second);
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_converter.pf(lvl, "template<>\n");
		s_outf_converter.pf(lvl, "void rcver::register_callback<mid_t::%s>(std::function< void(std::function<void(struct %s&)>)> f)\n", evt_name, type_name);
		s_outf_converter.pf(lvl, "{\n");
		s_outf_converter.pf(lvl+1, "auto getter = [this](struct %s & dst) -> void {\n", type_name);
		s_outf_converter.pf(lvl+2, "json2c(dst, ((rapidjson::Document*)m_doc)->FindMember(\"data\")->value);\n");
		s_outf_converter.pf(lvl+1, "};\n");
		s_outf_converter.pf(lvl+1, "m_cbs[\"%s\"] = [getter, f]()->void {\n", evt_name);
		s_outf_converter.pf(lvl+2, "f(getter);\n");
		s_outf_converter.pf(lvl+1, "};\n");
		s_outf_converter.pf(lvl, "}\n\n");
	}
#endif
	/// mid to string
	s_outf_converter.pf(lvl, "/// mid to string\n");
	s_outf_converter.pf(lvl, "const char * rcver::__mid_to_str(mid_t mid)\n");
	s_outf_converter.pf(lvl, "{\n");
	s_outf_converter.pf(lvl+1, "return s_mid_to_str[(%s)mid];\n", s_mid_under_type);
	s_outf_converter.pf(lvl, "}\n\n");

	/// unpack
	s_outf_converter.pf(lvl, "/// messages unpack\n");
	for (const auto & itr: s_msg_order) {
		rapidjson::Value & val = *itr;
		const char * type_name = val.FindMember("name")->value.GetString();
		s_outf_converter.pf(lvl, "void rcver::__unpack(struct %s & dst)\n", type_name);
		s_outf_converter.pf(lvl, "{\n");
		s_outf_converter.pf(lvl+1, "json2c(dst, ((rapidjson::Document*)m_doc)->FindMember(s_data)->value);\n");
		s_outf_converter.pf(lvl, "}\n\n");
	}
}

void generate_msgs(rapidjson::Document & /*d*/)
{
	const std::size_t lvl = 0;

	gen_msg_enum(lvl);
	gen_msg_map(lvl);

	gen_msg_glb(lvl);

	generate_msg_sender_header(lvl);
	generate_msg_sender_implement(lvl);

	generate_msg_rcver_header(lvl);
	generate_msg_rcver_implement(lvl);
}
