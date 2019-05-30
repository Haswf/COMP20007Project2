function EDGEBREAKDOWN(graph, u, w, next)
	/* weight(u, w) - 1 is number of new vertexs needed*/
	for i ← 0 to WEIGHT(u, w) - 1 do
		ADDVERTEX(graph, next)
		/* it must be the first vertex */
		if (i == 0) then
			ADDEDGE(graph, u, next)
		else
			/* link it with vertex added in last iter */
			ADDEDGE(graph, prev, next)
		/* update prev */
		prev ← next
		next ← next + 1
	ADDEDGE(graph, prev, w)

function WEIGHTEDAPSP(<V,E>)
	/* initialise graph */
	graph ← INITIALISEGRAPH(V, E)

	size ← GETVERTEXNUMBER(graph)
	next ← GETVERTEXNUMBER(graph)
	for each e ∈ E do
		e = u, w
		distance = WEIGHT(u, w)
		/* Break long edge into edges of weigth 1 */
		if distance > 1 then
			EDGEBREAKDOWN(graph, u, w, next);
			next ← next + distance - 1
		
	SP = UNWEIGHTEDAPSP(graph) 

	for path ∈ SP do
		src, dest = path
		/* only keeps vertext and edges in original graph */
		if(src >= size or dest >= size) then
			POP(SP, path)
	print(SP)
