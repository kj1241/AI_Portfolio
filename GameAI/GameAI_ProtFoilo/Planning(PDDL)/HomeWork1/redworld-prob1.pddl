;; problem file: redworld-prob1.pddl

(define (problem redworld-prob1)
  (:domain redworld)
  (:objects red granny wolf woods red-house granny-house food)
  (:init (at red red-house) (at granny granny-house) (at wolf woods) 
        (alive red)   (alive granny)   (alive wolf) (having red food) (hungry wolf))
  (:goal (and (not (hungry wolf)) (alive wolf))))