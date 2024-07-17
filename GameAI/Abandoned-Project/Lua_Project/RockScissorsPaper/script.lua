-- ���� �߻��⸦ �ʱ�ȭ�մϴ�
math.randomseed(os.time())

-- �÷��̾�� ��ǻ���� ������ ������ ���� �������Դϴ�
player_score = 0
computer_score = 0

-- ���� ���� �����Դϴ�
while true do
    -- ���� ������ ����ڿ��� �˷��ݴϴ�
    print("\n\n�����: " .. player_score .. " ��ǻ��: " .. computer_score)
    print("����(r)/����(p)/��(s) �߿� �����ϼ���  [q�� ������ ����˴ϴ�]")

    -- ����ڷκ��� Ű���� �Է��� �޽��ϴ�
    local player_move = io.stdin:read("*l")

    -- ����� �Է��� �÷��� ���ڿ��� ��ȯ�ϴ� ���̺��� �����մϴ�
    local possible_moves = {r = "����", p = "��", s = "����"}

    if player_move == "q" then
        break -- ����ڰ� 'q'�� �Է��ϸ� ������ �����մϴ�
    elseif possible_moves[player_move] then
        local computer_move = GetComputerMove()

        -- C++ �Լ� EvaluateMoves���� ������Ʈ�� ������ �����ɴϴ�
        player_score, computer_score = EvaluateMoves(possible_moves[player_move], computer_move, player_score, computer_score)
    else
        print("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���")
    end
end
