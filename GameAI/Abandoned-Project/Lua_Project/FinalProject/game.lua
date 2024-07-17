-- game.lua
dofile("player.lua")
dofile("enemy.lua")
dofile("inventory.lua")

player = Player:new(nil, "Hero", 100, 10)

-- 여러 적 추가
enemies = {
    Enemy:new(nil, "Goblin1", 30, 10),
    Enemy:new(nil, "Goblin2", 40, 12),
    Enemy:new(nil, "Goblin3", 50, 14)
}

inventory = Inventory:new()

function startGame()
    print("게임을 시작합니다.")
end

function attack()
    print("공격할 적을 선택하세요:")
    for i, enemy in ipairs(enemies) do
        if enemy.hp > 0 then
            print(i .. ". " .. enemy.name .. " (체력: " .. enemy.hp .. ")")
        end
    end

    local choice = tonumber(io.read())
    local enemy = enemies[choice]

    print("-------------게임 로그----------------")
    if enemy and enemy.hp > 0 then
        player:attack(enemy)
        if enemy.hp <= 0 then
            print(enemy.name .. "을(를) 물리쳤습니다!")
        else
            local damage = enemy:attack(player)
            print(enemy.name .. "이(가) " .. player.name .. "에게 " .. damage .. "의 피해를 입혔습니다.")
        end
    else
        print("잘못된 선택입니다.")
    end

    checkEndCondition()

    print("--------------------------------------")
end

function useItem()
    inventory:useItem(player)
    checkEndCondition()
end

function showInventory()
    inventory:show()
end

function checkEndCondition()
    if player.hp <= 0 then
         print(player.name .. "가 사망했습니다!")
         print("패배하였습니다!")
         print("--------------------------------------")
        os.exit()
    end

    local allEnemiesDefeated = true
    for _, enemy in ipairs(enemies) do
        if enemy.hp > 0 then
            allEnemiesDefeated = false
            break
        end
    end

    if allEnemiesDefeated then
         print(player.name .. "가 승리했습니다!")
         print("--------------------------------------")
        os.exit()
    end
end
