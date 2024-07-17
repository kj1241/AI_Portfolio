-- inventory.lua
Inventory = {items = {}}

function Inventory:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.items = {"Potion", "Potion", "Potion"}  -- 여러 개의 포션 추가
    return o
end

function Inventory:show()
    print("인벤토리:")
    for i, item in ipairs(self.items) do
        print(i .. ". " .. item)
    end
end

function Inventory:useItem(player)
    if #self.items == 0 then
        print("사용할 아이템이 없습니다.")
        return
    end

    print("사용할 아이템을 선택하세요:")
    self:show()
    local choice = tonumber(io.read())

    if choice and choice > 0 and choice <= #self.items then
        local item = self.items[choice]
        if item == "Potion" then
            player.hp = player.hp + 20
            print("포션을 사용했습니다. 체력이 20 회복되었습니다. 현재 체력: " .. player.hp)
            table.remove(self.items, choice)
        end
    else
        print("잘못된 선택입니다.")
    end
end

return Inventory
