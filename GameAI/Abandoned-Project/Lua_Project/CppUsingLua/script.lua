-- 전역 변수 데모를 위한 Lua 스크립트

-- 전역 문자열 및 숫자 타입
name   = "연습용"
age    = 29

-- 전역 테이블 생성
simple_table = {name="김철수", age=24}

-- 두 숫자를 더하는 간단한 함수
function add(a, b)
    return (a + b)
end

-- 문자열을 출력하는 함수
function print_message(message)
    print("[Lua]: " .. message)
end

-- 테이블에 요소를 추가하는 함수
function add_to_table(tbl, key, value)
    tbl[key] = value
end

-- 변수 선언 및 초기화
a = 10
b = 20


-- 예시
print("[Lua]: 여기서 부터는 루아 스크립트 자체 출력 내용입니다.")

-- 더하기
print("\n더하기 예제입니다.")

sum = a + b
print("[Lua]: sum = " .. sum)

-- 조건문 예제
print("\n조건문 예제입니다.")

age = 21
if age < 18 then
    print("[Lua]: 미성년자입니다.")
else
    print("[Lua]: 성인입니다.")
end

-- for 루프 예제
print("\nFor문 예제입니다.")

for i = 1, 10 do
    print("[Lua]: i = " .. i)
end

-- while 루프 예제
print("\nWhile문 예제입니다.")

i = 1
while i <= 10 do
    print("[Lua]: i = " .. i)
    i = i + 1
end

-- 배열 예제
print("\n배열 예제입니다.")

array = {1, 2, 3, 4, 5}
for i = 1, #array do
    print("[Lua]: array[" .. i .. "] = " .. array[i])
end

-- 해시 테이블 예제
print("\n해시 테이블 예제입니다.")

person = {name = "홍길동", age = 30}
print("[Lua]: name = " .. person.name)
print("[Lua]: age = " .. person.age)


-- 함수 호출
print(" ")
print("함수 호출 예제입니다.")

function greet(name)
    return "안녕하세요, " .. name
end

message = greet("철수")
print("[Lua]: " .. message)


-- 클래스 상속 관련 Lua 코드
print(" ")
print("클래스 상속 예제입니다.")

-- Animal 클래스 정의
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

-- Animal 클래스의 인스턴스 생성 및 사용 예제
cat = Animal:new(4, "야옹이")
cat:Speak()
print ("고양이의 다리는: "..cat:GetNumLegs().." 개 입니다.")

-- Pet 클래스 정의 (Animal 상속)
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

-- Pet 클래스의 인스턴스 생성 및 사용 예제
dog = Pet:new("알버트", 4, "늑대")
dog:Speak()
print ("내 강아지의 이름은: "..dog:GetName())


-- 코루틴 사용 예제
print(" ")
print("코루틴 사용 예제입니다.")

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



print("\n[lua]: \"script.lua\" 스크립트 실행 완료")