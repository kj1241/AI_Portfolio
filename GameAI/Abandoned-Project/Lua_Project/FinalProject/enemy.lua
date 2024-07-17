-- enemy.lua
Enemy = {name = "", hp = 0, attackPower = 0}

function Enemy:new(o, name, hp, attackPower)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.name = name
    o.hp = hp
    o.attackPower = attackPower
    return o
end

function Enemy:attack(target)
    print(self.name .. "이(가) " .. target.name .. "을(를) 공격합니다!")
    target.hp = target.hp - self.attackPower
    print(target.name .. "의 남은 체력: " .. target.hp)
    return self.attackPower
end

return Enemy
