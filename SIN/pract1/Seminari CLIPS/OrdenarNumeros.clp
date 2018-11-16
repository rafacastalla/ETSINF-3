
  (deffacts dades
      (llista 4 5 3 46 12 10))

  (defrule ordenar
    ?f1 <- (llista $?x ?y ?z $?w)
	   (test (< ?z ?y))    ;; comprovem si ?z es menor que ?y
	=>
	   (retract ?f1)
	   (assert (llista $?x ?z ?y $?w)))   ;; intercanviem elements


   
