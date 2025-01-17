// Copyright 2016, Tobias Hermann.
// https://github.com/Dobiasd/frugally-deep
// Distributed under the MIT License.
// (See accompanying LICENSE file or at
//  https://opensource.org/licenses/MIT)

#pragma once

#include "fdeep/layers/global_pooling_layer.hpp"

#include <algorithm>
#include <limits>
#include <string>

namespace fdeep { namespace internal
{

class global_max_pooling_3d_layer : public global_pooling_layer
{
public:
    explicit global_max_pooling_3d_layer(const std::string& name, bool keepdims) :
    global_pooling_layer(name), keepdims_(keepdims)
    {
    }
protected:
    tensor pool(const tensor& in) const override
    {
        const auto out_dimensions = keepdims_ ?
            fplus::append_elem(in.shape().depth_, std::vector<std::size_t>(in.shape().rank() - 1, 1)) :
            fplus::singleton_seq(in.shape().depth_);
        tensor out(create_tensor_shape_from_dims(out_dimensions), 0);
        for (std::size_t z = 0; z < in.shape().depth_; ++z)
        {
            float_type val = std::numeric_limits<float_type>::lowest();
            for (std::size_t d4 = 0; d4 < in.shape().size_dim_4_; ++d4)
            {   
                for (std::size_t y = 0; y < in.shape().height_; ++y)
                {
                    for (std::size_t x = 0; x < in.shape().width_; ++x)
                    {
                        val = std::max(val, in.get_ignore_rank(tensor_pos(d4, y, x, z)));
                    }
                }
            }
            out.set_ignore_rank(tensor_pos(z), val);
        }
        return out;
    }
    bool keepdims_;
};

} } // namespace fdeep, namespace internal
