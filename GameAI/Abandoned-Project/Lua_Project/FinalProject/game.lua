-- game.lua
dofile("player.lua")
dofile("enemy.lua")
dofile("inventory.lua")

player = Player:new(nil, "Hero", 100, 10)

-- ���� �� �߰�
enemies = {
    Enemy:new(nil, "Goblin1", 30, 10),
    Enemy:new(nil, "Goblin2", 40, 12),
    Enemy:new(nil, "Goblin3", 50, 14)
}

inventory = Inventory:new()

function startGame()
    print("������ �����մϴ�.")
end

function attack()
    print("������ ���� �����ϼ���:")
    for i, enemy in ipairs(enemies) do
        if enemy.hp > 0 then
            print(i .. ". " .. enemy.name .. " (ü��: " .. enemy.hp .. ")")
        end
    end

    local choice = tonumber(io.read())
    local enemy = enemies[choice]

    print("-------------���� �α�----------------")
    if enemy and enemy.hp > 0 then
        player:attack(enemy)
        if enemy.hp <= 0 then
            print(enemy.name .. "��(��) �����ƽ��ϴ�!")
        else
            local damage = enemy:attack(player)
            print(enemy.name .. "��(��) " .. player.name .. "���� " .. damage .. "�� ���ظ� �������ϴ�.")
        end
    else
        print("�߸��� �����Դϴ�.")
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
         print(player.name .. "�� ����߽��ϴ�!")
         print("�й��Ͽ����ϴ�!")
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
         print(player.name .. "�� �¸��߽��ϴ�!")
         print("--------------------------------------")
        os.exit()
    end
end
