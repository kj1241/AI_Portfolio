-- ���� ���� ���� ���� Lua ��ũ��Ʈ

-- ���� ���ڿ� �� ���� Ÿ��
name   = "������"
age    = 29

-- ���� ���̺� ����
simple_table = {name="��ö��", age=24}

-- �� ���ڸ� ���ϴ� ������ �Լ�
function add(a, b)
    return (a + b)
end

-- ���ڿ��� ����ϴ� �Լ�
function print_message(message)
    print("[Lua]: " .. message)
end

-- ���̺� ��Ҹ� �߰��ϴ� �Լ�
function add_to_table(tbl, key, value)
    tbl[key] = value
end

-- ���� ���� �� �ʱ�ȭ
a = 10
b = 20


-- ����
print("[Lua]: ���⼭ ���ʹ� ��� ��ũ��Ʈ ��ü ��� �����Դϴ�.")

-- ���ϱ�
print("\n���ϱ� �����Դϴ�.")

sum = a + b
print("[Lua]: sum = " .. sum)

-- ���ǹ� ����
print("\n���ǹ� �����Դϴ�.")

age = 21
if age < 18 then
    print("[Lua]: �̼������Դϴ�.")
else
    print("[Lua]: �����Դϴ�.")
end

-- for ���� ����
print("\nFor�� �����Դϴ�.")

for i = 1, 10 do
    print("[Lua]: i = " .. i)
end

-- while ���� ����
print("\nWhile�� �����Դϴ�.")

i = 1
while i <= 10 do
    print("[Lua]: i = " .. i)
    i = i + 1
end

-- �迭 ����
print("\n�迭 �����Դϴ�.")

array = {1, 2, 3, 4, 5}
for i = 1, #array do
    print("[Lua]: array[" .. i .. "] = " .. array[i])
end

-- �ؽ� ���̺� ����
print("\n�ؽ� ���̺� �����Դϴ�.")

person = {name = "ȫ�浿", age = 30}
print("[Lua]: name = " .. person.name)
print("[Lua]: age = " .. person.age)


-- �Լ� ȣ��
print(" ")
print("�Լ� ȣ�� �����Դϴ�.")

function greet(name)
    return "�ȳ��ϼ���, " .. name
end

message = greet("ö��")
print("[Lua]: " .. message)


-- Ŭ���� ��� ���� Lua �ڵ�
print(" ")
print("Ŭ���� ��� �����Դϴ�.")

-- Animal Ŭ���� ����
Animal = {}
Animal.__index = Animal

function Animal:new(num_legs, noise_made)
    local instance = setmetatable({}, self)
    instance:__init(num_legs, noise_made)
    return instance
end

function Animal:__init(num_legs, noise_made)
    self.NoiseMade = noise_made
    self.NumLegs = num_legs
end

function Animal:Speak()
    print(self.NoiseMade)
end

function Animal:GetNumLegs()
    return self.NumLegs
end

-- Animal Ŭ������ �ν��Ͻ� ���� �� ��� ����
cat = Animal:new(4, "�߿���")
cat:Speak()
print ("������� �ٸ���: "..cat:GetNumLegs().." �� �Դϴ�.")

-- Pet Ŭ���� ���� (Animal ���)
Pet = setmetatable({}, {__index = Animal})
Pet.__index = Pet

function Pet:new(name, num_legs, noise_made)
    local instance = setmetatable(Animal:new(num_legs, noise_made), self)
    instance:__init(name, num_legs, noise_made)
    return instance
end

function Pet:__init(name, num_legs, noise_made)
    Animal.__init(self, num_legs, noise_made)
    self.Name = name
end

function Pet:GetName()
    return self.Name
end

-- Pet Ŭ������ �ν��Ͻ� ���� �� ��� ����
dog = Pet:new("�˹�Ʈ", 4, "����")
dog:Speak()
print ("�� �������� �̸���: "..dog:GetName())


-- �ڷ�ƾ ��� ����
print(" ")
print("�ڷ�ƾ ��� �����Դϴ�.")

local function worker()
      for i = 1, 5 do
          print("Worker: " .. i)
          coroutine.yield()
      end
  end

  local co = coroutine.create(worker)
  for i = 1, 5 do
      print("Main: " .. i)
      coroutine.resume(co)
  end



print("\n[lua]: \"script.lua\" ��ũ��Ʈ ���� �Ϸ�")