;; domain file: TheGiftOfMagi-domain.pddl

(define (domain TheGiftOfMagi)
  (:requirements :strips)

  (:predicates (sleep ?x)
               (haveWatch ?x)
               (haveHeir ?x)
               (loc ?x ?y)
               (ChristmasEve ?x)
               (wakeUp ?x)
               (BeforeChristmas ?x)
               (seeWatch ?x ?y)
               (seeHeir ?x ?y)
               (haveMomey ?x)
              
               
               (Store ?x ?y ?z)
               (haveComb ?x)
      
               (haveWire ?x)
               (Christmas ?x)
               (happy ?x))

  (:action wakeUp
           :parameters (?ob)
           :precondition (and (sleep ?ob))
           :effect (and (wakeUp ?ob) (not(sleep ?ob))))
           
  ;(:action See
  ;         :parameters (?ob ?x ?y)
  ;         :precondition (and (have ?x ?ob))
  ;         :effect (and (see ?y ?x ?ob) ))
  ; 실행시 시간이 오래걸려서 바꿈
  
  (:action SeeWatch
           :parameters (?x ?y)
           :precondition (and (haveWatch ?y) (wakeUp ?y) (wakeUp ?x))
           :effect (and (seeWatch ?x ?y) ))
  
  (:action SeeHeir
           :parameters (?x ?y)
           :precondition (and (haveHeir ?y)  (wakeUp ?y) (wakeUp ?x))
           :effect (and (seeHeir ?x ?y) ))
  
  
  (:action sleepChristmasEve
           :parameters (?k ?x ?y ?ob1 ?ob2)
           :precondition (and (ChristmasEve ?k) (seeHeir ?x ?y) (seeWatch ?y ?x)(haveHeir ?y) (haveWatch ?x))
           :effect (and (sleep ?x) (sleep ?y) (not(wakeUp ?x)) (not(wakeup ?y))))
           
           
  (:action BeforeChristmas
           :parameters (?ob ?x ?y)
           :precondition (and (sleep ?x) (sleep ?y) (ChristmasEve ?ob) (seeWatch ?x ?y) (seeHeir ?y ?x))
           :effect (and (BeforeChristmas ?ob) (not(ChristmasEve ?ob)) ))           
           
  (:action GoHeirShop
           :parameters (?x ?k)
           :precondition (and (haveHeir ?x) (wakeup ?x) (seewatch ?x ?k) )
           :effect (and (haveMomey ?x) (not(haveHeir ?x)) ))         
           
  (:action GoWatchShop
           :parameters (?x ?k)
           :precondition (and (havewatch ?x) (wakeup ?x) (seeHeir ?x ?k))
           :effect (and (haveMomey ?x) (not(haveWatch ?x)) ))
           
  (:action BuyComb
           :parameters (?x ?y)
           :precondition (and (haveMomey ?x) (wakeup ?x) (seeHeir ?x ?y))
           :effect (and (haveMomey ?x) (haveComb ?x) (not(haveMomey ?x)) ))
           
  (:action Buywire
           :parameters (?x  ?y)
           :precondition (and (haveMomey ?x) (wakeup ?x) (seewatch ?x ?y))
           :effect (and (haveMomey ?x) (haveWire ?x) (not(haveMomey ?x)) ))
           
          
 
   (:action sleepBeforChreismas
           :parameters (?D ?x ?y)
           :precondition (and (BeforeChristmas ?d) (haveWire ?x) (haveComb ?y))
           :effect (and (sleep ?x) (sleep ?y) (not(wakeUp ?x)) (not(wakeup ?y) )))
           
   (:action BeforeChristmas
           :parameters (?ob ?x ?y)
           :precondition (and (sleep ?x) (sleep ?y) (BeforeChristmas ?ob) (haveWire ?x) (haveComb ?y))
           :effect (and (Christmas ?ob) (not(BeforeChristmas ?ob)) ))       
           
  (:action eat
           :parameters (?ob ?x ?y)
           :precondition (and (wakeUp ?x) (wakeup ?y) (Christmas ?ob) (haveWire ?x) (haveComb ?y))
           :effect (and (haveWire ?y) (haveComb ?y)(happy ?x) (happy ?y) ))
           
           )  
