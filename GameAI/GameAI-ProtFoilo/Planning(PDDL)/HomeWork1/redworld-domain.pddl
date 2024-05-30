;; domain file: redworld-domain.pddl

(define (domain redworld)
  (:requirements :strips)

  (:predicates (at ?p ?loc)    ; ?p is at ?loc
                (hungry ?p)    ; ?p is hungry
                (dead ?p)
                (alive ?p)
               (having ?p ?obj)) ; ?p has ?obj
               

  (:action moveto
           :parameters (?p ?loc1 ?loc2)
           :precondition (and (at ?p ?loc1))
           :effect (and (at ?p ?loc2) (not (at ?p ?loc1))))

  (:action eat-alive
           :parameters (?p1 ?p2 ?loc)
           :precondition (and (hungry ?p1) (alive ?p1) (alive ?p2) (at ?p1 ?loc) (at ?p2 ?loc))
           :effect (and (dead ?p2) (not (dead ?p1)) (not (hungry ?p1))))


  (:action give
           :parameters (?p1 ?p2 ?obj)   ; ?p1 gives ?obj ?p2
           :precondition (and (having ?p1 ?obj))
           :effect (and (having ?p2 ?obj)
                        (not (having ?p1 ?obj)))))

 
