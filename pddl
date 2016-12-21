Init (On(A, Table) ∧ On(B, Table) ∧ On(C, A) ∧ Block (A) ∧ Block (B) ∧ Block (C) ∧ Clear (B) ∧ Clear (C))
Goal (On(A, B) ∧ On(B, C))
Action(Move(b, x, y),
	PRECOND : On(b, x) ∧ Clear (b) ∧ Clear (y) ∧ Block (b) ∧ Block (y) ∧ (b!=x) ∧ (b!=y) ∧ (x!=y),
	EFFECT : On(b, y) ∧ Clear (x) ∧ ¬On(b, x) ∧ ¬Clear (y))
Action(MoveToTable (b, x),
	PRECOND : On(b, x) ∧ Clear (b) ∧ Block (b) ∧ (b!=x),
	EFFECT : On(b, Table) ∧ Clear (x) ∧ ¬On(b, x))