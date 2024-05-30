;; domain file: turtleStory-domain.pddl


(define (domain turtleStory)
  (:requirements :strips)

  (:predicates (at ?p ?loc)    ; ?p is at ?loc
                (state ?x ?y)
                (having ?p ?obj) ; ?p has ?obj
               (sick ?p)
               (cure ?p)
               (hopital ?p)
               (Castle ?p)
               (loyalist ?p)
               (medicine ?p)
               (rabbitcheek ?p)
               (rabbitPoop ?p)
               (rabbitLiver ?p)
               (land ?p))
               

  (:action go_to_Castle_for_King
           :parameters (?x ?y ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (Castle ?x) (hopital ?y))
           :effect (and (Castle ?y) (not (hopital ?y))))
  (:action What_is_medicine
           :parameters (?x ?y ?z ?loc1)
           :precondition (and (at ?x ?loc1) (Castle ?x) (Castle ?y)(at ?z ?loc1))
           :effect (and (loyalist ?z) (medicine ?z)))

  (:action Find_rabbite
           :parameters (?x ?y ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (loyalist ?x) (at ?y ?loc2))
           :effect (and (at ?x ?loc2) (not(at ?x ?loc1))))   
           
  (:action go_to_move
           :parameters (?x ?y ?z ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (at ?y ?loc1) (at ?z ?loc2) (sick ?z))
           :effect (and (at ?x ?loc2) (at ?y ?loc2) (not(at ?x ?loc1)) (not(at ?y ?loc1)))) 
  (:action Truth
           :parameters (?x ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (rabbitcheek ?x) (rabbitLiver ?x) (land ?loc2))
           :effect (and (at ?x ?loc2) (not(at ?x ?loc1))(not(rabbitcheek ?x))))
           
  (:action Truth
           :parameters (?x ?y ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (rabbitcheek ?x) (rabbitLiver ?x) (land ?loc2) (at ?y ?loc1)(loyalist ?y))
           :effect (and (at ?x ?loc2) (at ?y ?loc2) (not(at ?x ?loc1))(not(rabbitcheek ?x))(not (at ?y ?loc1))))
 
  (:action take_out_medicine
           :parameters (?x ?y ?loc1)
           :precondition (and (at ?x ?loc1) (at ?y ?loc1) (loyalist ?x) (rabbitPoop ?y))
           :effect (and (rabbitPoop ?x) (not(rabbitPoop ?y)) ))
           
  (:action go_to_see
           :parameters (?x ?y ?loc1 ?loc2)
           :precondition (and (at ?x ?loc1) (at ?y ?loc2) (loyalist ?x) (sick ?y))
           :effect (and (at ?x ?loc2) (not(at ?x ?loc1)) ))
           
  (:action give_medicine
           :parameters (?x ?y )
           :precondition (and (loyalist ?x) (sick ?y) (rabbitPoop ?x))
           :effect (and (cure ?y) (not(sick ?y)) )))