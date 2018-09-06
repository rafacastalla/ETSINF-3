;; =========================================================
;; === H E U R I S T I C A   D E S C O L · L O C A D E S === 
;; =========================================================

(defglobal ?*nod-gen* = 0)
(defglobal ?*f* = 1)


(deffunction descolocades (?estat)
	(bind ?desc 0)
	
	(if (<> (nth$ 1 ?estat)  1) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 2 ?estat)  2) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 3 ?estat)  3) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 4 ?estat)  8) then  (bind ?desc (+ ?desc 1)))
	;; (if (<> (nth$ 5 ?estat)  0) then  (bind ?desc (+ ?desc 1)));;
	(if (<> (nth$ 6 ?estat)  4) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 7 ?estat)  7) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 8 ?estat)  6) then  (bind ?desc (+ ?desc 1)))
	(if (<> (nth$ 9 ?estat)  5) then  (bind ?desc (+ ?desc 1)))
       ?desc)


(deffunction control (?estat ?nivell)
(bind ?*f* (descolocades ?estat))
(bind ?*f* (+ ?*f* ?nivell 1)))


(defrule dreta
  (declare (salience (- 0 ?*f*)))
  ?f<-(puzle $?x 0 ?y $?z nivell ?nivell moviment ?mov fet ?)
  (profunditat-maxima ?prof)
  (test (and (<> (length$ $?x) 2) (<> (length$ $?x) 5)))
  (test (neq ?mov esquerra))
  (test (< ?nivell ?prof))
  (test (control (create$ $?x ?y 0 $?z) ?nivell))
  =>
  (assert (puzle $?x ?y 0 $?z nivell (+ ?nivell 1) moviment dreta fet ?f))
  (bind ?*nod-gen* (+ ?*nod-gen* 1)))


(defrule esquerra
  (declare (salience (- 0 ?*f*)))
  ?f<-(puzle $?x ?y 0 $?z nivell ?nivell moviment ?mov fet ?)
  (profunditat-maxima ?prof)
  (test (and (<> (length$ $?x) 2) (<> (length$ $?x) 5)))
  (test (neq ?mov dreta))
  (test (< ?nivell ?prof))
  (test (control (create$ $?x 0 ?y $?z) ?nivell))
  =>
  (assert (puzle $?x 0 ?y $?z nivell (+ ?nivell 1) moviment esquerra fet ?f))
  (bind ?*nod-gen* (+ ?*nod-gen* 1)))


(defrule baix
  (declare (salience (- 0 ?*f*)))
  ?f<-(puzle $?x 0 ?a ?b ?c $?z nivell ?nivell moviment ?mov fet ?)
 (profunditat-maxima ?prof)
 (test (neq ?mov dalt))
 (test (< ?nivell ?prof))
 (test (control (create$ $?x ?c ?a ?b 0 $?z) ?nivell))
=>
 (assert (puzle $?x ?c ?a ?b 0 $?z nivell (+ ?nivell 1) moviment baix fet ?f))
 (bind ?*nod-gen* (+ ?*nod-gen* 1)))


(defrule dalt
  (declare (salience (- 0 ?*f*)))
  ?f<-(puzle $?x ?a ?b ?c 0 $?z nivell ?nivell moviment ?mov fet ?)
  (profunditat-maxima ?prof)
  (test (neq ?mov baix))
  (test (< ?nivell ?prof))
  (test (control (create$ $?x 0 ?b ?c ?a $?z) ?nivell))
  =>
  (assert (puzle $?x 0 ?b ?c ?a $?z nivell (+ ?nivell 1) moviment dalt fet ?f))
  (bind ?*nod-gen* (+ ?*nod-gen* 1)))

;; ======================================================
;; =========    ESTRATÈGIA DE CONTROL DE CERCA   ========
;; ======================================================
;; La regla 'objectiu' s'utilitza per a detectar quan s'ha aconseguit l'estat objectiu

(defrule objectiu
     (declare (salience 100))
   ?f <-(puzle 1 2 3 8 0 4 7 6 5 nivell ?n moviment ?mov fet ?)
  =>
   (printout t "SOLUCIÓ TROBADA EN EL NIVELL " ?n crlf)
   (printout t "NOMBRE DE NODES EXPANDITS O REGLES DISPARADES " ?*nod-gen* crlf)
   (printout t "FET OBJECTIU " ?f crlf)
   (halt))


(defrule no_solucio
    (declare (salience -99))
    (puzle $? nivell ?n $?)
=>
    (printout t "SOLUCIÓ NO TROBADA" crlf)
    (printout t "NODES GENERATS: " ?*nod-gen* crlf)
    (halt))


(deffunction inici ()
   (set-salience-evaluation when-activated)
   (reset)
   (printout t "Profunditat Maxima:= " )
   (bind ?prof (read))
   (printout t " Executa run per a engegar el programa " crlf)
   (assert (puzle 2 8 3 1 6 4 7 0 5 nivell 0 moviment nul fet 0))
   (assert (profunditat-maxima ?prof)))


(deffunction cami
        (?f)
        (bind ?llista (fact-slot-value ?f implied))
        (bind ?l2 (member$ nivell ?llista))
        (bind ?n (nth (+ ?l2 1) ?llista))
        ;;(printout t "nivell=" ?n crlf)
        (bind ?dir (nth (length ?llista) ?llista))
        (bind ?mov (subseq$ ?llista (+ ?l2 3) (- (length ?llista) 2)))
        (bind ?path (create$ ?dir ?mov))
        ;;(printout t ?dir "    " ?mov crlf)

        (loop-for-count (- ?n 1)
                (bind ?llista (fact-slot-value (fact-index ?dir) implied))
                (bind ?dir (nth (length ?llista) ?llista))
                (bind ?l2 (member$ nivell ?llista))
                (bind ?mov (subseq$ ?llista (+ ?l2 3) (- (length ?llista) 2)))
                (bind ?path (create$ ?dir ?mov ?path))
        )

        (printout t "Camí: " ?path crlf)
)
