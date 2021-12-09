// make sure to include other sub effects
// use crate::file_name::ClassName

// class definition
pub struct Gain {
    // class members
    // member_name: member_type,
    g_value: f64

}

// implementation
impl Gain {
    // constructor
    pub fn new(value: f64) -> Self {
        Self {
            g_value: value,
        }
    }

    // process block
    // input can also be mono
    // input can also be array of tuples to process block at a time
    pub fn tick(&mut self, input: (f64, f64)) -> (f64, f64) {
        let mut output = (0.0, 0.0);

        output.0 = self.g_value * input.0;
        output.1 = self.g_value * input.1;

        return output;
    }

    // setters for members
    pub fn set_gain(&mut self, value: f64) {
        self.g_value = value;
    }
}

// test cases
#[cfg(test)]
mod tests {
    #[test]

    fn test_case() {
        // do some tests and use assert to verify results
        let mut gain = super::Gain::new(0.5);
        assert_eq!(gain.tick((0.8, 0.5)), (0.4, 0.25));
    }
}
