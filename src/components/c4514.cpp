//
// Created by sauvau_m on 3/2/17.
//

#include <algorithm>
#include "components/c4514.hpp"

nts::c4514::~c4514() {

}

nts::c4514::c4514(const std::string &name) : AComponent(name, 24) {
    //strobe
    pinComputeFunction[1] = std::bind(&c4514::input, this, 1);
    //inputs
    //A
    pinComputeFunction[2] = std::bind(&c4514::input, this, 2);
    //B
    pinComputeFunction[3] = std::bind(&c4514::input, this, 3);
    //C
    pinComputeFunction[21] = std::bind(&c4514::input, this, 21);
    //D
    pinComputeFunction[22] = std::bind(&c4514::input, this, 22);
    //inhibit
    pinComputeFunction[23] = std::bind(&c4514::input, this, 23);

    //outputs
    //s7
    pinComputeFunction[4] = std::bind(&c4514::output, this, 4);
    //s6
    pinComputeFunction[5] = std::bind(&c4514::output, this, 5);
    //s5
    pinComputeFunction[6] = std::bind(&c4514::output, this, 6);
    //s4
    pinComputeFunction[7] = std::bind(&c4514::output, this, 7);
    //s3
    pinComputeFunction[8] = std::bind(&c4514::output, this, 8);
    //s2
    pinComputeFunction[10] = std::bind(&c4514::output, this, 10);
    //s1
    pinComputeFunction[9] = std::bind(&c4514::output, this, 9);
    //s0
    pinComputeFunction[11] = std::bind(&c4514::output, this, 11);
    //s13
    pinComputeFunction[13] = std::bind(&c4514::output, this, 13);
    //s12
    pinComputeFunction[14] = std::bind(&c4514::output, this, 14);
    //s15
    pinComputeFunction[15] = std::bind(&c4514::output, this, 15);
    //s14
    pinComputeFunction[16] = std::bind(&c4514::output, this, 16);
    //s9
    pinComputeFunction[17] = std::bind(&c4514::output, this, 17);
    //s8
    pinComputeFunction[18] = std::bind(&c4514::output, this, 18);
    //s11
    pinComputeFunction[19] = std::bind(&c4514::output, this, 19);
    //s10
    pinComputeFunction[20] = std::bind(&c4514::output, this, 20);

    //vss
    pinComputeFunction[12] = std::bind(&c4514::vss, this, 12);
    //vdd
    pinComputeFunction[24] = std::bind(&c4514::vdd, this, 24);

    for (int i = 0; i < 16; ++i) {
        value[i] = UNDEFINED;
    }
    linkSToPin[11] = 0;
    linkSToPin[9] = 1;
    linkSToPin[10] = 2;
    linkSToPin[8] = 3;
    linkSToPin[7] = 4;
    linkSToPin[6] = 5;
    linkSToPin[5] = 6;
    linkSToPin[4] = 7;
    linkSToPin[18] = 8;
    linkSToPin[17] = 9;
    linkSToPin[20] = 10;
    linkSToPin[19] = 11;
    linkSToPin[14] = 12;
    linkSToPin[13] = 13;
    linkSToPin[16] = 14;
    linkSToPin[15] = 15;
}

nts::Tristate nts::c4514::output(size_t pin_num_this) {
    int r = 0;

    if (linkSToPin.find(pin_num_this) == linkSToPin.end())
        return UNDEFINED;
    if (Compute(1) == 0) {
        value[linkSToPin[pin_num_this]] = FALSE;
        return value[linkSToPin[pin_num_this]];
    }
    if (Compute(23) == 1) {
        return value[linkSToPin[pin_num_this]];
    }

    r |= Compute(2) << 0;
    r |= Compute(3) << 1;
    r |= Compute(21) << 2;
    r |= Compute(22) << 3;
    r == linkSToPin[pin_num_this] ? value[linkSToPin[pin_num_this]] = TRUE : value[linkSToPin[pin_num_this]] = FALSE;
    return value[linkSToPin[pin_num_this]];
}

void nts::c4514::Dump(void) const {
    AComponent::Dump("Component 4514 : ");
}
