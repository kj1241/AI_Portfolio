;; problem file: turtleStory-prob1.pddl

(define (problem turtleStory-prob1)
  (:domain turtleStory)
  (:objects turtle rabbit seeking see land sick rabbitLiver doctor rabbitPoop cure rabbitcheek)
  (:init (at seeking see) (at doctor see) (at turtle see) (at rabbit land)    (hopital doctor) (Castle seeking) (loyalist turtle)
        (state seeking sick) (rabbitcheek rabbit) (rabbitPoop rabbit) (rabbitLiver rabbit) (sick seeking) (land land))
  (:goal (or(cure seeking))))