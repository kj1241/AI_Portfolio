-- ���� �߻��⸦ �ʱ�ȭ�մϴ�
math.randomseed(os.time())

-- 1~100������ ���� ���ڸ� ����ϴ�.
local targetNumber = math.random(1, 100)

-- ���� ���߱� �Լ�
function guessNumber(guess)
    if guess == targetNumber then
        return 0  -- ���߸� 0 ��ȯ
    elseif guess < targetNumber then
        return -1 -- ������ �� ũ�� -1 ��ȯ
    elseif guess > targetNumber then
        return 1  -- ������ �� ������ 1 ��ȯ
    else
        return 2
    end
end