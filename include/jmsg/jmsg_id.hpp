
/**
 * generated based on idl, please don't modify it.
 */
#pragma once

#include "jmsg_types.hpp"

#define DCL_MSG(_x) msg_helper<mid_t::_x>::value_type

enum class mid_t : uint16_t {
	nil = 0,	/// occupy symbol, correspond to \em NULL.
	arc_revise = 1,
	defect_detect_result = 2,
	discharge = 3,
	discharge_adjust_init = 4,
	discharge_adjust_result = 5,
	discharge_adjust_start = 6,
	discharge_count = 7,
	dust_check_full_result = 8,
	dust_check_full_start = 9,
	dust_check_result = 10,
	dust_check_start = 11,
	fiber_reco_result = 12,
	fiber_train_init = 13,
	fiber_train_result = 14,
	fiber_train_start = 15,
	fs_cover_openned = 16,
	fs_cover_state = 17,
	fs_state = 18,
	fusion_splice_reset = 19,
	fusion_splice_result = 20,
	fusion_splice_start = 21,
	get_fiber_defect_info = 22,
	go_on = 23,
	heat_result = 24,
	heat_start = 25,
	heat_state = 26,
	image_move = 27,
	loss_estimating_result = 28,
	manual_discharge_counts = 29,
	motor_start = 30,
	motor_stop = 31,
	motor_test_result = 32,
	motor_test_start = 33,
	process_progress = 34,
	query_dev_state = 35,
	query_wave_form = 36,
	realtime_revise_result = 37,
	realtime_revise_start = 38,
	record_offset = 39,
	regular_test_result = 40,
	regular_test_start = 41,
	report_dev_state = 42,
	report_wave_form = 43,
	set_fs_display_mode = 44,
	set_fs_display_mode_ext = 45,
	set_fs_display_zoom_ext = 46,
	set_lcd_brightness = 47,
	set_led = 48,
	set_window = 49,
	skip = 50,
	stabilize_electrode_result = 51,
	stabilize_electrode_start = 52,
	stop = 53,
	stop_discharge = 54,
	tense_test_result = 55,
};
template<mid_t mid>
struct msg_helper final {};

template<>
struct msg_helper<mid_t::arc_revise> final {
	typedef struct arc_revise value_type;
};

template<>
struct msg_helper<mid_t::defect_detect_result> final {
	typedef struct defect_detect_result value_type;
};

template<>
struct msg_helper<mid_t::discharge> final {
	typedef struct discharge value_type;
};

template<>
struct msg_helper<mid_t::discharge_adjust_init> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::discharge_adjust_result> final {
	typedef struct discharge_adjust_result value_type;
};

template<>
struct msg_helper<mid_t::discharge_adjust_start> final {
	typedef struct fs_da_cfg value_type;
};

template<>
struct msg_helper<mid_t::discharge_count> final {
	typedef struct discharge_count value_type;
};

template<>
struct msg_helper<mid_t::dust_check_full_result> final {
	typedef struct dust_check_result value_type;
};

template<>
struct msg_helper<mid_t::dust_check_full_start> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::dust_check_result> final {
	typedef struct dust_check_result value_type;
};

template<>
struct msg_helper<mid_t::dust_check_start> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::fiber_reco_result> final {
	typedef struct fiber_reco_result value_type;
};

template<>
struct msg_helper<mid_t::fiber_train_init> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::fiber_train_result> final {
	typedef struct fiber_train_result value_type;
};

template<>
struct msg_helper<mid_t::fiber_train_start> final {
	typedef struct fs_ft_cfg value_type;
};

template<>
struct msg_helper<mid_t::fs_cover_openned> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::fs_cover_state> final {
	typedef struct fs_cover_state value_type;
};

template<>
struct msg_helper<mid_t::fs_state> final {
	typedef struct fs_state value_type;
};

template<>
struct msg_helper<mid_t::fusion_splice_reset> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::fusion_splice_result> final {
	typedef struct fusion_splice_result value_type;
};

template<>
struct msg_helper<mid_t::fusion_splice_start> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::get_fiber_defect_info> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::go_on> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::heat_result> final {
	typedef struct heat_result value_type;
};

template<>
struct msg_helper<mid_t::heat_start> final {
	typedef struct heat_start value_type;
};

template<>
struct msg_helper<mid_t::heat_state> final {
	typedef struct heat_state value_type;
};

template<>
struct msg_helper<mid_t::image_move> final {
	typedef struct image_move value_type;
};

template<>
struct msg_helper<mid_t::loss_estimating_result> final {
	typedef struct loss_estimating_result value_type;
};

template<>
struct msg_helper<mid_t::manual_discharge_counts> final {
	typedef struct manual_discharge_counts value_type;
};

template<>
struct msg_helper<mid_t::motor_start> final {
	typedef struct motor_start value_type;
};

template<>
struct msg_helper<mid_t::motor_stop> final {
	typedef struct motor_stop value_type;
};

template<>
struct msg_helper<mid_t::motor_test_result> final {
	typedef struct motor_test_result value_type;
};

template<>
struct msg_helper<mid_t::motor_test_start> final {
	typedef struct fs_mt_cfg value_type;
};

template<>
struct msg_helper<mid_t::process_progress> final {
	typedef struct process_progress value_type;
};

template<>
struct msg_helper<mid_t::query_dev_state> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::query_wave_form> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::realtime_revise_result> final {
	typedef struct realtime_revise_result value_type;
};

template<>
struct msg_helper<mid_t::realtime_revise_start> final {
	typedef struct fs_rr_cfg value_type;
};

template<>
struct msg_helper<mid_t::record_offset> final {
	typedef struct record_offset value_type;
};

template<>
struct msg_helper<mid_t::regular_test_result> final {
	typedef struct regular_test_result value_type;
};

template<>
struct msg_helper<mid_t::regular_test_start> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::report_dev_state> final {
	typedef struct report_dev_state value_type;
};

template<>
struct msg_helper<mid_t::report_wave_form> final {
	typedef struct report_wave_form value_type;
};

template<>
struct msg_helper<mid_t::set_fs_display_mode> final {
	typedef struct set_fs_display_mode value_type;
};

template<>
struct msg_helper<mid_t::set_fs_display_mode_ext> final {
	typedef struct set_fs_display_mode_ext value_type;
};

template<>
struct msg_helper<mid_t::set_fs_display_zoom_ext> final {
	typedef struct set_fs_display_zoom_ext value_type;
};

template<>
struct msg_helper<mid_t::set_lcd_brightness> final {
	typedef struct set_lcd_brightness value_type;
};

template<>
struct msg_helper<mid_t::set_led> final {
	typedef struct set_led value_type;
};

template<>
struct msg_helper<mid_t::set_window> final {
	typedef struct set_window value_type;
};

template<>
struct msg_helper<mid_t::skip> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::stabilize_electrode_result> final {
	typedef struct stabilize_electrode_result value_type;
};

template<>
struct msg_helper<mid_t::stabilize_electrode_start> final {
	typedef struct fs_se_cfg value_type;
};

template<>
struct msg_helper<mid_t::stop> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::stop_discharge> final {
	typedef struct simple_msg value_type;
};

template<>
struct msg_helper<mid_t::tense_test_result> final {
	typedef struct tense_test_result value_type;
};

