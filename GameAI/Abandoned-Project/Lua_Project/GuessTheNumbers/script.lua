-- 난수 발생기를 초기화합니다
math.randomseed(os.time())

-- 1~100사이의 랜덤 숫자를 만듭니다.
local targetNumber = math.random(1, 100)

-- 숫자 맞추기 함수
function guessNumber(guess)
    if guess == targetNumber then
        return 0  -- 맞추면 0 반환
    elseif guess < targetNumber then
        return -1 -- 정답이 더 크면 -1 반환
    elseif guess > targetNumber then
        return 1  -- 정답이 더 작으면 1 반환
    else
        return 2
    end
end