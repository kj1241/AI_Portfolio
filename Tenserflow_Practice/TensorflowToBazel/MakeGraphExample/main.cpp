#include <iostream>
#include <cstring> // std::memcpy를 사용하기 위한 헤더
#include <tensorflow/c/c_api.h>

/// 그래프 생성 함수
TF_Graph* CreateGraph() {
    // 새로운 그래프 객체 생성
    TF_Graph* graph = TF_NewGraph();
    TF_Status* status = TF_NewStatus();

    // 상수 노드 생성
    TF_OperationDescription* const_desc = TF_NewOperation(graph, "Const", "const_node");
    float const_val = 3.0f;
    TF_Tensor* const_tensor = TF_AllocateTensor(TF_FLOAT, nullptr, 0, sizeof(float));
    std::memcpy(TF_TensorData(const_tensor), &const_val, sizeof(float));
    TF_SetAttrTensor(const_desc, "value", const_tensor, status);
    TF_SetAttrType(const_desc, "dtype", TF_FLOAT);
    TF_Operation* const_op = TF_FinishOperation(const_desc, status);

    // 에러 체크
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "Error: " << TF_Message(status) << std::endl;
        TF_DeleteGraph(graph);
        graph = nullptr;
    }

    // 메모리 해제
    TF_DeleteStatus(status);
    TF_DeleteTensor(const_tensor);

    return graph;
}

// 그래프 실행 함수
float RunGraph(TF_Graph* graph) {
    float result = 0.0f;
    TF_Status* status = TF_NewStatus();
    TF_SessionOptions* sess_opts = TF_NewSessionOptions();
    TF_Session* session = TF_NewSession(graph, sess_opts, status);

    // 출력값 설정
    TF_Output output = { TF_GraphOperationByName(graph, "const_node"), 0 };
    TF_Tensor* output_tensor = nullptr;

    // 세션 실행
    TF_SessionRun(session,
        nullptr, // run_options
        nullptr, nullptr, 0, // inputs
        &output, &output_tensor, 1, // outputs
        nullptr, 0, // target operations
        nullptr, // run_metadata
        status);

    // 결과 확인
    if (TF_GetCode(status) == TF_OK) {
        float* data = static_cast<float*>(TF_TensorData(output_tensor));
        result = *data;
    }
    else {
        std::cerr << "Error: " << TF_Message(status) << std::endl;
    }

    // 메모리 해제
    TF_DeleteStatus(status);
    TF_DeleteSession(session, status);
    TF_DeleteSessionOptions(sess_opts);
    TF_DeleteTensor(output_tensor);

    return result;
}

int main() {
    // 그래프 생성
    TF_Graph* graph = CreateGraph();
    if (graph == nullptr) {
        std::cerr << "그래프 생성 실패" << std::endl;
        return 1;
    }

    // 그래프 실행
    float result = RunGraph(graph);
    std::cout << "Result: " << result << std::endl;

    // 그래프 삭제
    TF_DeleteGraph(graph);

    return 0;
}