FUNCTION MINMAXWEIGHT(<V,E>,V0)
	for each v in V do
		width[v] = INF
		prev[v] = NO_PREV
	width[v] = 0
	Q = INITPRIORITYQUEUE(V) // Priorities are width
	while Q is not empty do
		u = EJECTMIN(Q)
		for each(u, w) in E do
			if w in Q and MAX(width[u], width[v]) < width[w] then
				width[w] = MAX(width[u], width[v])
				prev[w] = u
			UPDATEQUEUE(Q, w, width[w])