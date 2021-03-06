
/**
 * generated based on idl, please don't modify it.
 */
#pragma once
#include <map>
#include <string>
#include <functional>

#include "jmsg_id.hpp"


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
	void __pack(const struct fs_state & val);
	void __pack(const struct heat_state & val);
	void __pack(const struct simple_msg & val);
	void __pack(const struct record_offset & val);
	void __pack(const struct tense_test_result & val);
	void __pack(const struct loss_estimating_result & val);
	void __pack(const struct defect_detect_result & val);
	void __pack(const struct fiber_reco_result & val);
	void __pack(const struct manual_discharge_counts & val);
	void __pack(const struct fusion_splice_result & val);
	void __pack(const struct arc_revise & val);
	void __pack(const struct fs_da_cfg & val);
	void __pack(const struct discharge_adjust_result & val);
	void __pack(const struct discharge & val);
	void __pack(const struct discharge_count & val);
	void __pack(const struct set_fs_display_mode_ext & val);
	void __pack(const struct set_fs_display_zoom_ext & val);
	void __pack(const struct set_fs_display_mode & val);
	void __pack(const struct dust_check_result & val);
	void __pack(const struct heat_start & val);
	void __pack(const struct heat_result & val);
	void __pack(const struct image_move & val);
	void __pack(const struct set_window & val);
	void __pack(const struct fs_cover_state & val);
	void __pack(const struct set_lcd_brightness & val);
	void __pack(const struct set_led & val);
	void __pack(const struct motor_start & val);
	void __pack(const struct motor_stop & val);
	void __pack(const struct fs_mt_cfg & val);
	void __pack(const struct motor_test_result & val);
	void __pack(const struct process_progress & val);
	void __pack(const struct fs_rr_cfg & val);
	void __pack(const struct realtime_revise_result & val);
	void __pack(const struct regular_test_result & val);
	void __pack(const struct fs_se_cfg & val);
	void __pack(const struct stabilize_electrode_result & val);
	void __pack(const struct report_dev_state & val);
	void __pack(const struct report_wave_form & val);
	void __pack(const struct fs_ft_cfg & val);
	void __pack(const struct fiber_train_result & val);

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


