;;COMPROVAR SI LA CONFIGURACION GENERADA TÉ SOLUCIÓ
;;com utilitzem una configuració final fixa, aquesta sempre té valor 11 
;;es conta, per a cada valor, quants valors menors queden a la seua dreta 
;;se sumen tots aquests valors i ha de donar un valor imparell (per a que inicial+final siga parell) 

(deffunction comprovar_conf (?list)
	(bind ?suma 0)
	(bind ?i 1)
        (bind ?list (replace-member$ ?list 9 0))   
	(while (<= ?i 9)
		(bind ?value (integer (nth 1 (subseq$ $?list ?i ?i))))
		;;(printout t ?value crlf)
		(bind ?cont 0)
		(bind ?j (+ 1 ?i))
		(while (<= ?j 9)
			(if (> ?value (integer (nth 1 (subseq$ $?list ?j ?j)))) then
				(bind ?cont (+ 1 ?cont))
			) 
			(bind ?j (+ 1 ?j))
		) 
		(bind ?suma (+ ?cont ?suma))
		(bind ?i (+ 1 ?i))
	)
        (bind ?pos_cero (member 9 ?list))	;;; EVA
        (bind ?row_cero (div ?pos_cero 3))	;;; EVA
        (bind ?col_cero (mod ?pos_cero 3))	;;; EVA
        (if (evenp (+ ?row_cero ?col_cero)) then (bind ?suma (+ ?suma 1)))	;;; EVA
	(<> (mod ?suma 2) 0)
) 