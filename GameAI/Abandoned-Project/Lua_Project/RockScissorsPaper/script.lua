-- 난수 발생기를 초기화합니다
math.randomseed(os.time())

-- 플레이어와 컴퓨터의 점수를 저장할 전역 변수들입니다
player_score = 0
computer_score = 0

-- 메인 게임 루프입니다
while true do
    -- 현재 점수를 사용자에게 알려줍니다
    print("\n\n사용자: " .. player_score .. " 컴퓨터: " .. computer_score)
    print("가위(r)/바위(p)/보(s) 중에 선택하세요  [q를 누르면 종료됩니다]")

    -- 사용자로부터 키보드 입력을 받습니다
    local player_move = io.stdin:read("*l")

    -- 사용자 입력을 플레이 문자열로 변환하는 테이블을 생성합니다
    local possible_moves = {r = "바위", p = "보", s = "가위"}

    if player_move == "q" then
        break -- 사용자가 'q'를 입력하면 게임을 종료합니다
    elseif possible_moves[player_move] then
        local computer_move = GetComputerMove()

        -- C++ 함수 EvaluateMoves에서 업데이트된 점수를 가져옵니다
        player_score, computer_score = EvaluateMoves(possible_moves[player_move], computer_move, player_score, computer_score)
    else
        print("잘못된 입력입니다. 다시 시도하세요")
    end
end
