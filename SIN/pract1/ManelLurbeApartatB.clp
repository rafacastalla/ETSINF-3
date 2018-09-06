(defglobal ?*f* = 0)
(defglobal ?*nod-gen* = 0)

(deffacts camins
  (cami A B 10 bici)
  (cami A C 8 peu)
  (cami A E 10 bici)
  (cami B C 5 peu)
  (cami B F 6 peu)
  (cami C D 6 peu)
  (cami C G 6 peu)
  (cami D H 14 bici)
  (cami E I 20 peu)
  (cami E J 9 bici)
  (cami F K 10 peu)
  (cami F L 6 peu)
  (cami G H 8 peu)
  (cami G L 9 peu)
  (cami G M 12 peu)
  (cami H I 12 bici)
  (cami I O 2 peu)
  (cami J O 7 bici)
  (cami K L 2 bici)
  (cami L M 7 bici)
  (cami L P 6 bici)
  (cami M Q 2 peu)
  (cami N O 8 bici)
  (cami N Q 6 peu)
  (cami P Q 2 peu)
  (cami P R 4 bici)
  (cami Q R 3 peu)
  (base A B H J K M N R)

  (barri 1 A)
  (barri 2 B C D E J)
  (barri 3 F G H I O)
  (barri 4 K L M N)
  (barri 5 P Q)
  (barri 6 R)
)

(deffunction inici ()
	;(set-strategy depth)
	(set-strategy breadth)
	(set-salience-evaluation when-activated)
  (reset)

	(printout t "Node orige:= " )
	(bind ?orige (read))

	(printout t "Node desti:= " )
	(bind ?desti (read))

  (printout t "Profunditat Maxima:= " )
	(bind ?prof (read))

  (printout t " Executa run per a engegar el programa " crlf)
	(assert (actual ?orige onvaig ?desti hemcosta 0 bici no nivell 0 pMax ?prof ruta ?orige))
)

(defrule inicialitzarMinim
  (declare (salience 1000))
  (or (cami ?a ?x ?c $?bici) (cami ?x ?a ?c $?bici))
  =>
  (assert (camiminim ?a x 900))
)

(deffunction control (?g ?orige ?desti ?min ?sit)
  (bind ?h (abs (- ?orige ?desti)))
  (if (= ?h 0) then
        (bind ?h 1)
  )

  (bind ?h (* ?h ?min))
  (bind ?h (* ?h (round ?sit)))

  (bind ?h (+ ?h ?g))

  (bind ?*f* ?h)
)

(defrule camMin
  (declare (salience 999))
	(actual ?a onvaig ? hemcosta ? bici $? nivell ? pMax ? ruta $?)
  (or (cami ?a ?x ?cost $?) (cami ?x ?a ?cost $?))
  ?f1 <- (camiminim ?a ? ?costMinim)
  (test (< ?cost ?costMinim))
  =>
  (retract ?f1)
  (assert (camiminim ?a ?x ?cost))
)

(defrule anarapeu
	(declare (salience (- 0 ?*f*)))
	?f1 <- (actual ?x onvaig ?y hemcosta ?c bici no nivell ?n pMax ?prof ruta $?r)
	(or (cami ?x ?b ?cost ?tipo) (cami ?b ?x ?cost ?tipo))

	(barri ?orige $? ?x $?)
  (barri ?desti $? ?y $?)
	(camiminim ?x ? ?min)

	(test (< ?n ?prof))
	(test (control ?c ?orige ?desti ?min 1))
	=>
	(bind ?*nod-gen* (+ ?*nod-gen* 1))
	(assert (actual ?b onvaig ?y hemcosta (+ ?c ?cost) bici no nivell (+ ?n 1) pMax ?prof ruta $?r ?b))
)

(defrule anarbici
  (declare (salience (- 0 ?*f*)))
	?f1 <- (actual ?x onvaig ?y hemcosta ?c bici si nivell ?n pMax ?prof ruta $?r)
	(or (cami ?x ?b ?cost bici) (cami ?b ?x ?cost bici))

	(barri ?orige $? ?x $?)
  (barri ?desti $? ?y $?)
	(camiminim ?x ? ?min)

	(test (< ?n ?prof))
  (test (control ?c ?orige ?desti ?min 0.5))
	=>
	(bind ?*nod-gen* (+ ?*nod-gen* 1))
	(assert (actual ?b onvaig ?y hemcosta (+ ?c (div ?cost 2)) bici si nivell (+ ?n 1) pMax ?prof ruta $?r ?b))
)

(defrule agafarbici
	(declare (salience (- 0 ?*f*)))
	?f1 <- (actual ?x onvaig ?y hemcosta ?c bici no nivell ?n pMax ?prof ruta $?r)
  (base $?p ?x $?s)

	(barri ?orige $? ?x $?)
  (barri ?desti $? ?y $?)
	(camiminim ?x ? ?min)

	(test (< ?n ?prof))
  (test (control ?c ?orige ?desti ?min 0.5))
	=>
	(bind ?*nod-gen* (+ ?*nod-gen* 1))
	(assert (actual ?x onvaig ?y hemcosta (+ ?c 1) bici si nivell (+ ?n 1) pMax ?prof ruta $?r))
)

(defrule deixarbici
	(declare (salience (- 0 ?*f*)))
	?f1<-(actual ?x onvaig ?y hemcosta ?c bici si nivell ?n pMax ?prof ruta $?r)
	(base $?p ?x $?s)

  (barri ?orige $? ?x $?)
  (barri ?desti $? ?y $?)
  (camiminim ?x ? ?min)

	(test (< ?n ?prof))
	(test (control ?c ?orige ?desti ?min 0.5))
	=>
	(bind ?*nod-gen* (+ ?*nod-gen* 1))
	(assert (actual ?x onvaig ?y hemcosta (+ 1 ?c) bici no nivell (+ ?n 1) pMax ?prof  ruta $?r))
)

(defrule parada
  (declare (salience 1000))
	?f1<-(actual ?x onvaig ?x hemcosta ?cost bici no nivell ?nivell pMax ?prof ruta $?ruta)
	=>
	(printout t "Solucio trobada" crlf)
  (printout t "La ruta es: " $?ruta crlf)
  (printout t "Objectiu de profunditat: " ?nivell crlf)
  (printout t "Nodes generats: " ?*nod-gen* crlf)
  (printout t "Amb cost: " ?cost crlf)
	(halt)
)

(defrule error
  (declare (salience -1000))
	?f1<-(actual ?x onvaig ?x hemcosta ?cost bici no nivell ?nivell pMax ?prof ruta $?ruta)
	=>
	(printout t "ERROR: Solucio no trobada" crlf)
  (printout t "ERROR: La ruta es: " $?ruta crlf)
  (printout t "ERROR: Objectiu de profunditat: " ?nivell crlf)
  (printout t "ERROR: Nodes generats: " ?*nod-gen* crlf)
  (printout t "ERROR: Amb cost: " ?cost crlf)
	(halt)
)
