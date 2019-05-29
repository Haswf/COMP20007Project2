FUNCTION MINMAXWEIGHT(<V,E>,vs)
	/* initialise width, cost, prev */
	for each v ∈ V do
		width[v] ← ∞
		cost[v] ← ∞
		previous[v] ← nil
	
	/* set cost of vs to 0 */
	cost[vs] ← 0
	/* set width of vs to 0 */
	width[vs] ← 0
	/* vs has no previous point */
	previous[vs] = NIL

	/* initialise priority by adding vertex and maxWidth to each vertex as priority */
	Q = INITPRIORITYQUEUE(V) // Priorities are width
	while Q is non-empty do
		u ← EJECTMIN(Q)
		for each(u, w) ∈ E do
			/* if edge u,w has smaller maxWidth than width[w]*/
			if w ∈ Q and MAX(width[u], weight[u, w]) < width[w] then
				width[w] = MAX(width[u], weight[u, w])
				cost[w] = cost[u] + weight(u,w)
				previous[w] = u
				UPDATEQUEUE(Q, w, width[w])
	// print cost
	print(cost[ve])

	// Using while to print path until vs has been reached
	prev = previous[ve]
	while prev != vs do
		print(prev)
		prev ← previous[prev]