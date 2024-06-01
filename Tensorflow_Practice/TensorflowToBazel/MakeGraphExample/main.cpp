#include <iostream>
#include <cstring> // std::memcpy�� ����ϱ� ���� ���
#include <tensorflow/c/c_api.h>

/// �׷��� ���� �Լ�
TF_Graph* CreateGraph() {
    // ���ο� �׷��� ��ü ����
    TF_Graph* graph = TF_NewGraph();
    TF_Status* status = TF_NewStatus();

    // ��� ��� ����
    TF_OperationDescription* const_desc = TF_NewOperation(graph, "Const", "const_node");
    float const_val = 3.0f;
    TF_Tensor* const_tensor = TF_AllocateTensor(TF_FLOAT, nullptr, 0, sizeof(float));
    std::memcpy(TF_TensorData(const_tensor), &const_val, sizeof(float));
    TF_SetAttrTensor(const_desc, "value", const_tensor, status);
    TF_SetAttrType(const_desc, "dtype", TF_FLOAT);
    TF_Operation* const_op = TF_FinishOperation(const_desc, status);

    // ���� üũ
    if (TF_GetCode(status) != TF_OK) {
        std::cerr << "Error: " << TF_Message(status) << std::endl;
        TF_DeleteGraph(graph);
        graph = nullptr;
    }

    // �޸� ����
    TF_DeleteStatus(status);
    TF_DeleteTensor(const_tensor);

    return graph;
}

// �׷��� ���� �Լ�
float RunGraph(TF_Graph* graph) {
    float result = 0.0f;
    TF_Status* status = TF_NewStatus();
    TF_SessionOptions* sess_opts = TF_NewSessionOptions();
    TF_Session* session = TF_NewSession(graph, sess_opts, status);

    // ��°� ����
    TF_Output output = { TF_GraphOperationByName(graph, "const_node"), 0 };
    TF_Tensor* output_tensor = nullptr;

    // ���� ����
    TF_SessionRun(session,
        nullptr, // run_options
        nullptr, nullptr, 0, // inputs
        &output, &output_tensor, 1, // outputs
        nullptr, 0, // target operations
        nullptr, // run_metadata
        status);

    // ��� Ȯ��
    if (TF_GetCode(status) == TF_OK) {
        float* data = static_cast<float*>(TF_TensorData(output_tensor));
        result = *data;
    }
    else {
        std::cerr << "Error: " << TF_Message(status) << std::endl;
    }

    // �޸� ����
    TF_DeleteStatus(status);
    TF_DeleteSession(session, status);
    TF_DeleteSessionOptions(sess_opts);
    TF_DeleteTensor(output_tensor);

    return result;
}

int main() {
    // �׷��� ����
    TF_Graph* graph = CreateGraph();
    if (graph == nullptr) {
        std::cerr << "�׷��� ���� ����" << std::endl;
        return 1;
    }

    // �׷��� ����
    float result = RunGraph(graph);
    std::cout << "Result: " << result << std::endl;

    // �׷��� ����
    TF_DeleteGraph(graph);

    return 0;
}