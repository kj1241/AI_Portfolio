-- inventory.lua
Inventory = {items = {}}

function Inventory:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.items = {"Potion", "Potion", "Potion"}  -- ���� ���� ���� �߰�
    return o
end

function Inventory:show()
    print("�κ��丮:")
    for i, item in ipairs(self.items) do
        print(i .. ". " .. item)
    end
end

function Inventory:useItem(player)
    if #self.items == 0 then
        print("����� �������� �����ϴ�.")
        return
    end

    print("����� �������� �����ϼ���:")
    self:show()
    local choice = tonumber(io.read())

    if choice and choice > 0 and choice <= #self.items then
        local item = self.items[choice]
        if item == "Potion" then
            player.hp = player.hp + 20
            print("������ ����߽��ϴ�. ü���� 20 ȸ���Ǿ����ϴ�. ���� ü��: " .. player.hp)
            table.remove(self.items, choice)
        end
    else
        print("�߸��� �����Դϴ�.")
    end
end

return Inventory
