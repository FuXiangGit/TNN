// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tflite_op_converter.h"

namespace TNN_CONVERTER {
DECLARE_OP_CONVERTER(Pad);

std::string TFLitePadConverter::TNNOpType(bool quantizedModel) {
    return "Pad";
}

TNN_NS::Status TFLitePadConverter::exec(
    TNN_NS::NetStructure& net_structure, TNN_NS::NetResource& net_resource,
    const std::unique_ptr<tflite::OperatorT>& tf_lite_operator,
    const std::vector<std::unique_ptr<tflite::TensorT>>& tf_lite_tensors,
    const std::vector<std::unique_ptr<tflite::BufferT>>& tf_lite_model_buffer,
    const std::vector<std::unique_ptr<tflite::OperatorCodeT>>& tf_lite_op_set, bool quantizedModel) {
    TNN_NS::PadLayerParam* param = new TNN_NS::PadLayerParam;
    auto cur_layer                = net_structure.layers.back();
    auto tf_lite_op_type          = tf_lite_op_set[tf_lite_operator->opcode_index]->builtin_code;

    switch (tf_lite_op_type) {
        case tflite::BuiltinOperator_PAD: {
            param->type = 0;
            param->pads.push_back(0);
            param->pads.push_back(0);
            param->pads.push_back(0);
            param->pads.push_back(0);
            break;
        }
        default:{
            LOGE("TFLitePadConverter do not support ");
            return TNN_NS::TNNERR_CONVERT_UNSUPPORT_LAYER;
        }
    }
    // update param
    cur_layer->param = std::shared_ptr<TNN_NS::LayerParam>(param);

    return TNN_NS::TNN_CONVERT_OK;
}

using namespace tflite;
REGISTER_CONVERTER(Pad, BuiltinOperator_PAD);
}