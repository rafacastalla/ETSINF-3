(deffacts bf (cap X 4) (cap Y 3) (aig X 0 Y 0))
(defrule omplirX (cap X ?capX) (aig X ?x Y ?y)
  (test (< ?x ?capX)) => (assert (aig X ?capX Y ?y)))
(defrule omplirY (cap Y ?capY) (aig X ?x Y ?y)
  (test (< ?y ?capY)) => (assert (aig X ?x Y ?capY)))
(defrule buidarX (aig X ?x Y ?y)
  (test (> ?x 0)) => (assert (aig X 0 Y ?y)))
(defrule buidarY (aig X ?x Y ?y)
  (test (> ?y 0)) => (assert (aig X ?x Y 0)))
(defrule omplirXdesdY
  (cap X ?capX) (aig X ?x Y ?y)
  (test (> ?y 0)) (test (< ?x ?capX))
  (test (>= (+ ?x ?y) ?capX)) =>
  (assert (aig X ?capX Y (- ?y (- ?capX ?x)))))
(defrule omplirYdesdX
  (cap Y ?capY) (aig X ?x Y ?y)
  (test (> ?x 0)) (test (< ?y ?capY))
  (test (>= (+ ?x ?y) ?capY)) =>
  (assert (aig X (- ?x (- ?capY ?y)) Y ?capY)))
(defrule buidarXenY
  (cap Y ?capY) (aig X ?x Y ?y)
  (test (> ?x 0)) (test (<= (+ ?x ?y) ?capY)) =>
  (assert (aig X 0 Y (+ ?x ?y))))
(defrule buidarYenX
  (cap X ?capX) (aig X ?x Y ?y)
  (test (> ?y 0)) (test (<= (+ ?x ?y) ?capX)) =>
  (assert (aig X (+ ?x ?y) Y 0)))
(defrule obj
  (aig X 2 Y ?) => (printout t "Solucio trobada!" crlf) (halt))