// Copyright 2016, Tobias Hermann.
// https://github.com/Dobiasd/frugally-deep
// Distributed under the MIT License.
// (See accompanying LICENSE file or at
//  https://opensource.org/licenses/MIT)

#pragma once

#include "frugally_deep/layers/layer.h"

namespace fdeep
{

class input_layer : public layer
{
public:
    explicit input_layer(const std::string& name, const shape3& input_size)
        : layer(name), input_size_(input_size), output_()
    {
    }
protected:
    tensor3s apply_impl(const tensor3s& inputs) const override
    {
        assertion(inputs.size() == 1, "need exactly one input");
        assertion(inputs[0].size() == input_size_, "invalid input size");
        return inputs;
    }
    shape3 input_size_;

    // provide initial tensor for computation
    mutable fplus::maybe<tensor3> output_;
};

} // namespace fdeep