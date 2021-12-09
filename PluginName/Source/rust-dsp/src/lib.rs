mod gain;

#[no_mangle]
pub extern "C" fn create(value: f64) -> *mut gain::Gain {
    return Box::into_raw(Box::new(gain::Gain::new(value)));
}

#[no_mangle]
pub extern "C" fn destroy(gain: *mut gain::Gain) {
    if !gain.is_null() {
        unsafe {
            Box::from_raw(gain);
        }
    }
    else {
        panic!("");
    }
}

#[no_mangle]
pub unsafe extern "C" fn process(
    gain: &mut gain::Gain,
    input_l: *const f32,
    input_r: *const f32,
    output_l: *mut f32,
    output_r: *mut f32,
    sample_count: usize,
) {
    for i in 0..sample_count as isize {
        let out = gain.tick((*input_l.offset(i) as f64, *input_r.offset(i) as f64));
        *output_l.offset(i) = out.0 as f32;
        *output_r.offset(i) = out.1 as f32;
    }
}

#[no_mangle]
pub extern "C" fn set_gain(gain: &mut gain::Gain, value: f64) {
    gain.set_gain(value);
}
