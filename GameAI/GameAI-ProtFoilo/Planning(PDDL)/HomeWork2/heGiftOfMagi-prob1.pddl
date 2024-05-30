;; problem file: TheGiftOfMagi-prob1.pddl

(define (problem TheGiftOfMagi-prob1)
  (:domain TheGiftOfMagi)
  (:objects Della jim house Day)
  (:init (sleep Della) (sleep jim) (haveWatch jim) (haveHeir Della) (loc Della house) (loc jim house) (ChristmasEve Day))
  (:goal (and (Christmas Day))))
