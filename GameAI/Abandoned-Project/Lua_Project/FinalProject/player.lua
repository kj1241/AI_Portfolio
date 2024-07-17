-- player.lua
Player = {name = "", hp = 0, attackPower = 0}

function Player:new(o, name, hp, attackPower)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.name = name
    o.hp = hp
    o.attackPower = attackPower
    return o
end

function Player:attack(target)
    print(self.name .. "이(가) " .. target.name .. "을(를) 공격합니다!")
    target.hp = target.hp - self.attackPower
    print(target.name .. "의 남은 체력: " .. target.hp)
end

return Player
