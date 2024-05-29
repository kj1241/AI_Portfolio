#include <iostream>
#include <cstring> // std::memcpy를 사용하기 위한 헤더
#include <tensorflow/c/c_api.h>

void NoOpDeallocator(void* data, size_t len, void* arg) {
    // 아무 작업도 수행하지 않음
}

void DeallocateBuffer(void* data, size_t) {
    free(data);
}

TF_Buffer* ReadFile(const char* filename) {
    FILE* f = nullptr;
    fopen_s(&f, filename, "rb");
    if (f == nullptr) return nullptr;
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    void* data = malloc(fsize);
    fread(data, fsize, 1, f);
    fclose(f);

    return TF_NewBufferFromString(data, fsize);
}

int main() {
    // 모델 파일을 읽음
    const char* filename = "../MakeModelToPython/model.pb"; // 모델 파일 경로
    TF_Buffer* buffer = ReadFile(filename);
    if (buffer == nullptr) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return 1;
    }

    // TensorFlow 초기화
    TF_Status* status = TF_NewStatus();
    TF_Graph* graph = TF_NewGraph();
    TF_SessionOptions* sess_opts = TF_NewSessionOptions();
    TF_Session* session = TF_NewSession(graph, sess_opts, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "세션 생성 실패: " << TF_Message(status) << std::endl;
        TF_DeleteBuffer(buffer);
        TF_DeleteSessionOptions(sess_opts);
        TF_DeleteGraph(graph);
        TF_DeleteStatus(status);
        return 1;
    }
    std::cerr << "세션 생성 성공: " << TF_Message(status) << std::endl;

    // 모델 로드
    TF_ImportGraphDefOptions* graph_opts = TF_NewImportGraphDefOptions();
    TF_GraphImportGraphDef(graph, buffer, graph_opts, status);
    TF_DeleteBuffer(buffer);
    TF_DeleteImportGraphDefOptions(graph_opts);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "그래프 로드 실패: " << TF_Message(status) << std::endl;
        TF_DeleteSession(session, status);
        TF_DeleteSessionOptions(sess_opts);
        TF_DeleteGraph(graph);
        TF_DeleteStatus(status);
        return 1;
    }
    std::cerr << "그래프 로드 성공: " << TF_Message(status) << std::endl;
    //TF_DeleteImportGraphDefOptions(graph_opts);
    //TF_DeleteBuffer(buffer); // 그래프를 로드한 후에 버퍼를 해제함

    // 학습 데이터 정의 (여기서는 간단한 예제 데이터 사용)
    const int num_samples = 4;
    const float x_train[] = { 1.0, 2.0, 3.0, 4.0 };
    const float y_train[] = { 2.0, 3.0, 4.0, 5.0 };

    // 변수 정의
    TF_Operation* x_op;
    TF_Operation* y_op;
    TF_Operation* w_op; // 첫 번째 층의 가중치
    TF_Operation* b_op; // 첫 번째 층의 편향
    //TF_Operation* w2_op; // 두 번째 층의 가중치
    //TF_Operation* b2_op; // 두 번째 층의 편향
    TF_Operation* hypothesis_op;
    TF_Operation* loss_op;
    TF_Operation* train_op;

    auto cleanup = [&]() {
        TF_DeleteSession(session, status);
        TF_DeleteSessionOptions(sess_opts);
        TF_DeleteGraph(graph);
        TF_DeleteStatus(status);
    };


    TF_OperationDescription* desc;
    // 입력 플레이스홀더 정의
     // 입력 플레이스홀더 정의
    desc = TF_NewOperation(graph, "Placeholder", "x");
    TF_SetAttrType(desc, "dtype", TF_FLOAT);
    x_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "x 플레이스홀더 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }

    desc = TF_NewOperation(graph, "Placeholder", "y");
    TF_SetAttrType(desc, "dtype", TF_FLOAT);
    y_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "y 플레이스홀더 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }

    // 첫 번째 층의 변수 정의
    desc = TF_NewOperation(graph, "VariableV2", "w");
    TF_SetAttrType(desc, "dtype", TF_FLOAT);
    TF_SetAttrShape(desc, "shape", nullptr, 0);
    w_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "w 변수 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }


    desc = TF_NewOperation(graph, "VariableV2", "b");
    TF_SetAttrType(desc, "dtype", TF_FLOAT);
    TF_SetAttrShape(desc, "shape", nullptr, 0);
    b_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "b 변수 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }


    //// 두 번째 층의 변수 정의
    //desc = TF_NewOperation(graph, "VariableV2", "w2");
    //TF_SetAttrType(desc, "dtype", TF_FLOAT);
    //TF_SetAttrShape(desc, "shape", nullptr, 0);
    //w2_op = TF_FinishOperation(desc, status);

    //desc = TF_NewOperation(graph, "VariableV2", "b2");
    //TF_SetAttrType(desc, "dtype", TF_FLOAT);
    //TF_SetAttrShape(desc, "shape", nullptr, 0);
    //b2_op = TF_FinishOperation(desc, status);

    //// 첫 번째 층의 활성화 함수 정의 (ReLU)
    //TF_Operation* relu_op;
    //{
    //    TF_OperationDescription* relu_desc = TF_NewOperation(graph, "Relu", "relu");
    //    TF_AddInput(relu_desc, { x_op, 0 });
    //    relu_op = TF_FinishOperation(relu_desc, status);
    //}


    //// 첫 번째 층의 출력 계산
    //TF_Operation* layer1_output_op;
    //{
    //    TF_OperationDescription* matmul_desc = TF_NewOperation(graph, "MatMul", "layer1_output");
    //    TF_AddInput(matmul_desc, { relu_op, 0 }); // 입력
    //    TF_AddInput(matmul_desc, { w1_op, 0 }); // 첫 번째 층의 가중치
    //    layer1_output_op = TF_FinishOperation(matmul_desc, status);
    //}

    //// 두 번째 층의 활성화 함수 정의 (ReLU)
    //TF_Operation* relu2_op;
    //{
    //    TF_OperationDescription* relu2_desc = TF_NewOperation(graph, "Relu", "relu2");
    //    TF_AddInput(relu2_desc, { layer1_output_op, 0 }); // 첫 번째 층의 출력
    //    relu2_op = TF_FinishOperation(relu2_desc, status);
    //}

    //// 두 번째 층의 출력 계산 (최종 예측값)
    //{
    //    TF_OperationDescription* matmul2_desc = TF_NewOperation(graph, "MatMul", "hypothesis");
    //    TF_AddInput(matmul2_desc, { relu2_op, 0 }); // 두 번째 층의 출력
    //    TF_AddInput(matmul2_desc, { w2_op, 0 }); // 두 번째 층의 가중치
    //    hypothesis_op = TF_FinishOperation(matmul2_desc, status);
    //}

    //// 손실 함수 정의 (Mean Squared Error)
    //TF_Operation* sub_op;
    //{
    //    TF_OperationDescription* sub_desc = TF_NewOperation(graph, "Sub", "sub");
    //    TF_AddInput(sub_desc, { hypothesis_op, 0 }); // 예측값
    //    TF_AddInput(sub_desc, { y_op, 0 }); // 실제값
    //    sub_op = TF_FinishOperation(sub_desc, status);
    //}

    //TF_Operation* square_op;
    //{
    //    TF_OperationDescription* square_desc = TF_NewOperation(graph, "Square", "square");
    //    TF_AddInput(square_desc, { sub_op, 0 }); // 예측값 - 실제값의 제곱
    //    square_op = TF_FinishOperation(square_desc, status);
    //}

    //{
    //    TF_OperationDescription* mean_desc = TF_NewOperation(graph, "Mean", "loss");
    //    TF_AddInput(mean_desc, { square_op, 0 }); // 제곱의 평균
    //    loss_op = TF_FinishOperation(mean_desc, status);
    //}

    // 가중치와 바이어스 초기화 연산 정의
    desc = TF_NewOperation(graph, "Assign", "w_assign");
    TF_AddInput(desc, { w_op, 0 });
    TF_Operation* zero_w_op;
    {
        TF_OperationDescription* const_desc = TF_NewOperation(graph, "Const", "zero_w");
        TF_SetAttrType(const_desc, "dtype", TF_FLOAT);
        TF_Tensor* tensor = TF_AllocateTensor(TF_FLOAT, nullptr, 0, sizeof(float));
        float value = 1.0;
        memcpy(TF_TensorData(tensor), &value, sizeof(float));
        TF_SetAttrTensor(const_desc, "value", tensor, status);
        zero_w_op = TF_FinishOperation(const_desc, status);
        TF_DeleteTensor(tensor);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "zero_w 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }
    TF_AddInput(desc, { zero_w_op, 0 });
    TF_Operation* w_assign_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "w_assign 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }

    desc = TF_NewOperation(graph, "Assign", "b_assign");
    TF_AddInput(desc, { b_op, 0 });
    TF_Operation* zero_b_op;
    {
        TF_OperationDescription* const_desc = TF_NewOperation(graph, "Const", "zero_b");
        TF_SetAttrType(const_desc, "dtype", TF_FLOAT);
        TF_Tensor* tensor = TF_AllocateTensor(TF_FLOAT, nullptr, 0, sizeof(float));
        float value = 1.0;
        memcpy(TF_TensorData(tensor), &value, sizeof(float));
        TF_SetAttrTensor(const_desc, "value", tensor, status);
        zero_b_op = TF_FinishOperation(const_desc, status);
        TF_DeleteTensor(tensor);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "zero_b 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }
    TF_AddInput(desc, { zero_b_op, 0 });
    TF_Operation* b_assign_op = TF_FinishOperation(desc, status);
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "b_assign 생성 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }

    // 예측 함수 정의 (hypothesis = x * w + b)
    TF_Operation* mul_op;
    {
        TF_OperationDescription* mul_desc = TF_NewOperation(graph, "Mul", "mul");
        TF_AddInput(mul_desc, { x_op, 0 });
        TF_AddInput(mul_desc, { w_op, 0 });
        mul_op = TF_FinishOperation(mul_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "mul 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    {
        TF_OperationDescription* add_desc = TF_NewOperation(graph, "Add", "hypothesis");
        TF_AddInput(add_desc, { mul_op, 0 });
        TF_AddInput(add_desc, { b_op, 0 });
        hypothesis_op = TF_FinishOperation(add_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "hypothesis 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    // 손실 함수 정의 (loss = (hypothesis - y)^2)
    TF_Operation* sub_op;
    {
        TF_OperationDescription* sub_desc = TF_NewOperation(graph, "Sub", "sub");
        TF_AddInput(sub_desc, { hypothesis_op, 0 });
        TF_AddInput(sub_desc, { y_op, 0 });
        sub_op = TF_FinishOperation(sub_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "sub 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    TF_Operation* square_op;
    {
        TF_OperationDescription* square_desc = TF_NewOperation(graph, "Square", "square");
        TF_AddInput(square_desc, { sub_op, 0 });
        square_op = TF_FinishOperation(square_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "square 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }
    {
        TF_OperationDescription* mean_desc = TF_NewOperation(graph, "Mean", "loss");
        TF_AddInput(mean_desc, { square_op, 0 });

        // 축 정보 추가
        TF_Operation* axis_op;
        {
            int64_t dims[] = { 1 };
            int32_t axis[] = { 0 };
            TF_Tensor* axis_tensor = TF_AllocateTensor(TF_INT32, dims, 1, sizeof(axis));
            memcpy(TF_TensorData(axis_tensor), axis, sizeof(axis));
            TF_OperationDescription* axis_desc = TF_NewOperation(graph, "Const", "axis");
            TF_SetAttrType(axis_desc, "dtype", TF_INT32);
            TF_SetAttrTensor(axis_desc, "value", axis_tensor, status);
            axis_op = TF_FinishOperation(axis_desc, status);
            TF_DeleteTensor(axis_tensor);
            if (TF_GetCode(status) != TF_OK) {
                std::cerr << "axis 생성 중 오류 발생: " << TF_Message(status) << std::endl;
                cleanup();
                return 1;
            }
        }
        TF_AddInput(mean_desc, { axis_op, 0 });

        loss_op = TF_FinishOperation(mean_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "loss 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    // 가중치와 바이어스에 대한 그래디언트를 계산하는 연산 정의
    TF_Operation* grad_w_op;
    TF_Operation* grad_b_op;
    {
        TF_OperationDescription* grad_w_desc = TF_NewOperation(graph, "Sub", "grad_w");
        TF_AddInput(grad_w_desc, { w_op, 0 });
        TF_AddInput(grad_w_desc, { loss_op, 0 });
        grad_w_op = TF_FinishOperation(grad_w_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "grad_w 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }

        TF_OperationDescription* grad_b_desc = TF_NewOperation(graph, "Sub", "grad_b");
        TF_AddInput(grad_b_desc, { b_op, 0 });
        TF_AddInput(grad_b_desc, { loss_op, 0 });
        grad_b_op = TF_FinishOperation(grad_b_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "grad_b 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    // 학습률 정의
    TF_Operation* alpha_op;
    {
        float learning_rate = 0.01;
        TF_Tensor* alpha_tensor = TF_AllocateTensor(TF_FLOAT, nullptr, 0, sizeof(float));
        memcpy(TF_TensorData(alpha_tensor), &learning_rate, sizeof(float));
        TF_OperationDescription* alpha_desc = TF_NewOperation(graph, "Const", "alpha");
        TF_SetAttrType(alpha_desc, "dtype", TF_FLOAT);
        TF_SetAttrTensor(alpha_desc, "value", alpha_tensor, status);
        alpha_op = TF_FinishOperation(alpha_desc, status);
        TF_DeleteTensor(alpha_tensor);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "alpha 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    // 가중치 업데이트 연산 정의
    TF_Operation* update_w_op;
    TF_Operation* update_b_op;
    {
        TF_OperationDescription* update_w_desc = TF_NewOperation(graph, "ApplyGradientDescent", "update_w");
        TF_AddInput(update_w_desc, { w_op, 0 });
        TF_AddInput(update_w_desc, { alpha_op, 0 });
        TF_AddInput(update_w_desc, { grad_w_op, 0 });
        update_w_op = TF_FinishOperation(update_w_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "update_w 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }

        TF_OperationDescription* update_b_desc = TF_NewOperation(graph, "ApplyGradientDescent", "update_b");
        TF_AddInput(update_b_desc, { b_op, 0 });
        TF_AddInput(update_b_desc, { alpha_op, 0 });
        TF_AddInput(update_b_desc, { grad_b_op, 0 });
        update_b_op = TF_FinishOperation(update_b_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "update_b 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    // 학습 연산 정의

    {
        TF_OperationDescription* train_desc = TF_NewOperation(graph, "NoOp", "train");
        TF_AddControlInput(train_desc, update_w_op);
        TF_AddControlInput(train_desc, update_b_op);
        train_op = TF_FinishOperation(train_desc, status);
        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "train 생성 중 오류 발생: " << TF_Message(status) << std::endl;
            cleanup();
            return 1;
        }
    }

    //const TF_Operation* init_ops[] = { w_assign_op, b_assign_op };

    //TF_SessionRun(session,
    //    nullptr, // run options
    //    nullptr, nullptr, 0, // inputs
    //    nullptr, nullptr, 0, // outputs
    //    init_ops, 2, // target operations
    //    nullptr, // run metadata
    //    status);

    //if (TF_GetCode(status) != TF_OK) {
    //    std::cerr << "변수 초기화 실패: " << TF_Message(status) << std::endl;
    //    cleanup();
    //    return 1;
    //}

    //for (int i = 0; i < 1000; ++i) {
    //    // 학습 데이터를 텐서로 변환
    //    const int64_t dims[] = { num_samples };
    //    TF_Tensor* x_tensor = TF_AllocateTensor(TF_FLOAT, dims, 1, sizeof(x_train));
    //    TF_Tensor* y_tensor = TF_AllocateTensor(TF_FLOAT, dims, 1, sizeof(y_train));
    //    memcpy(TF_TensorData(x_tensor), x_train, sizeof(x_train));
    //    memcpy(TF_TensorData(y_tensor), y_train, sizeof(y_train));

    //    // 학습 실행
    //    TF_Output inputs[] = { { x_op, 0 }, { y_op, 0 } };
    //    TF_Tensor* input_values[] = { x_tensor, y_tensor };
    //    TF_Output outputs[] = { { train_op, 0 } };
    //    TF_Tensor* output_values[] = { nullptr };

    //    TF_SessionRun(session, nullptr,
    //        inputs, input_values, 2,
    //        outputs, output_values, 1,
    //        nullptr, 0, nullptr, status);

    //    // TF_DeleteTensor 호출 순서 및 위치 조정
    //    if (TF_GetCode(status) != TF_OK) {
    //        std::cerr << "학습 실행 중 오류 발생: " << TF_Message(status) << std::endl;
    //        TF_DeleteTensor(x_tensor);
    //        TF_DeleteTensor(y_tensor);
    //        cleanup();
    //        return 1;
    //    }

    //    TF_DeleteTensor(x_tensor);
    //    TF_DeleteTensor(y_tensor);

    //    if (i % 100 == 0) {
    //        std::cerr << "학습 반복 " << i << " 완료" << std::endl;
    //    }
    //}

    TF_Operation* init_ops[] = { w_assign_op, b_assign_op };

    TF_SessionRun(session,
        nullptr, // RunOptions
        nullptr, nullptr, 0, // Inputs
        nullptr, nullptr, 0, // Outputs
        init_ops, 2, // Target operations
        nullptr, // RunMetadata
        status);

    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "변수 초기화 중 오류 발생: " << TF_Message(status) << std::endl;
        cleanup();
        return 1;
    }

    for (int i = 0; i < 1000; ++i) {
        // 학습 데이터를 텐서로 변환
        const int64_t dims[] = { num_samples };
        TF_Tensor* x_tensor = TF_AllocateTensor(TF_FLOAT, dims, 1, num_samples * sizeof(float));
        TF_Tensor* y_tensor = TF_AllocateTensor(TF_FLOAT, dims, 1, num_samples * sizeof(float));
        memcpy(TF_TensorData(x_tensor), x_train, num_samples * sizeof(float));
        memcpy(TF_TensorData(y_tensor), y_train, num_samples * sizeof(float));

        // 학습 실행
        TF_Output inputs[] = { { x_op, 0 }, { y_op, 0 } };
        TF_Tensor* input_values[] = { x_tensor, y_tensor };
        const TF_Operation* train_ops[] = { train_op };

        TF_SessionRun(session, nullptr,
            inputs, input_values, 2,
            nullptr, nullptr, 0,
            train_ops, 1,
            nullptr, status);

        if (TF_GetCode(status) != TF_OK) {
            std::cerr << "학습 실행 중 오류 발생: " << TF_Message(status) << std::endl;
            TF_DeleteTensor(x_tensor);
            TF_DeleteTensor(y_tensor);
            cleanup();
            return 1;
        }

        TF_DeleteTensor(x_tensor);
        TF_DeleteTensor(y_tensor);

        if (i % 100 == 0) {
            std::cerr << "학습 반복 " << i << " 완료" << std::endl;
        }
    }

    // 로드한 모델로 예측
    const int64_t pred_dims[] = { 10 };
    TF_Tensor* pred_x_tensor = TF_AllocateTensor(TF_FLOAT, pred_dims, 1, 10 * sizeof(float));
    memcpy(TF_TensorData(pred_x_tensor), x_train, 10 * sizeof(float));

    TF_Output pred_inputs[] = { { x_op, 0 } };
    TF_Tensor* pred_input_values[] = { pred_x_tensor };
    TF_Output pred_outputs[] = { { hypothesis_op, 0 } };
    TF_Tensor* pred_output_values[1] = { nullptr };

    TF_SessionRun(session, nullptr,
        pred_inputs, pred_input_values, 1,
        pred_outputs, pred_output_values, 1,
        nullptr, 0,
        nullptr, status);

    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "예측 실행 중 오류 발생: " << TF_Message(status) << std::endl;
        TF_DeleteTensor(pred_x_tensor);
        cleanup();
        return 1;
    }

    // 예측 결과 출력
    float* predictions = static_cast<float*>(TF_TensorData(pred_output_values[0]));
    std::cerr << "예측 결과: ";
    for (int i = 0; i < 10; ++i) {
        std::cerr << predictions[i] << " ";
    }
    std::cerr << std::endl;

    TF_DeleteTensor(pred_x_tensor);
    TF_DeleteTensor(pred_output_values[0]);

    cleanup();
    return 0;
}