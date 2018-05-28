#test math
import numpy as np
import scipy.linalg as spla
from numpy import linalg as npla

def readVector(path):
	A = np.loadtxt(path)
	A2 = np.matrix(A).T
	return A2

def deltaRel(a, b):
	return abs(a - b)/abs(a)
#
def matVariation_(A, B):
	A2 = np.absolute(A)
	B2 = np.absolute(B)
	k = np.amax(B2)
	R = np.absolute(A2 - B2) / k
	return R
#
def matVariation(A, B):
	V = matVariation_(A, B)
	return np.array([np.amin(V), np.amax(V)])
#
def normFrobenius(A):
	return np.linalg.norm(A, 'fro')
#	
def matMaxElem(A):
	M = np.absolute(A)
	return np.amax(M)
#
def nFr(A):
	return normFrobenius(A) / matMaxElem(A)
#
def distFrobenius(A, B):
	D = A - B
	return np.linalg.norm(D, 'fro')
#
def dFr(A, B):
	F = distFrobenius(A, B)
	dA = matMaxElem(A)
	dB = matMaxElem(B)
	return F / matMaxElem(A - B)
#
def mkVec(size):
	return np.zeros((size, 1))
#
def mkVec_e(size, index):
	R = mkVec(size)
	R[index] = 1
	return R
#	
def lsolve(A, b):
	return np.linalg.solve(A, b)
#
def trace(A):
	return A.trace()

def det(A):
	return np.linalg.det(A)

def inv(A):
	return np.linalg.inv(A)
#
def mkVecByDig(value, size):
	return np.full((size, 1), value)

path_G7 = "..\\Gilbert7_o.prn"
G7_o = np.loadtxt(open(path_G7, "rb"), delimiter="\t", skiprows=0)
#print(G7_o)#print(G7_o.shape)
path_detG7 = "..\\detGilbert7_o.prn"
det_G7_o = np.loadtxt(open(path_detG7, "rb"), delimiter="\t", skiprows=0)
#print(det_G7_o)
det_G7_t = np.linalg.det(G7_o) #print(det_G7_t)
print(deltaRel(det_G7_o, det_G7_t))
#
path_invG7 = "..\\invG7_o.prn"
inv_G7_o = np.loadtxt(path_invG7)
#print(inv_G7_o)
inv_G7_t = np.linalg.inv(G7_o)
#print(inv_G7_t)
#
#frobG7_o = normFrobenius(inv_G7_o)
#print("Fr(inv_G7_o) =", frobG7_o)
#frobG7_t = normFrobenius(inv_G7_t)
#print("Fr(inv_G7_t) =", frobG7_t)
#
#print(matVariation_(inv_G7_t, inv_G7_o))
#print(matVariation(inv_G7_t, inv_G7_o))
#
#print("nFr(inv_G7_t) =", nFr(inv_G7_t))
#print("nFr(inv_G7_o) =", nFr(inv_G7_o))
#print("distFrob =", distFrobenius(inv_G7_t, inv_G7_o))
#print("dFr =", dFr(inv_G7_t, inv_G7_o))
#
#b_p47_o = mkVec_e(7, 0)
#print(b_p47_o)
#d_p47_t = lsolve(G7_o, b_p47_o)
#print("d_p47_t =", d_p47_t)
#path_d_p47_o = "..\\d_p47_o.prn"
#d_p47_o = readVector(path_d_p47_o)
#print("d_p47_o =", d_p47_o)
#print(matVariation(d_p47_t, d_p47_o))
#
#complex matr
#m1C = np.array([[2+3.j, 1-4.j], [3+4.j, 5+6.j]], dtype=complex)
#print(m1C)
#print(trace(m1C))
#print("matAbs =", np.absolute(m1C))
#print("nFr(m1C) =", nFr(m1C))
#M_forLU1 = np.array([[4,3],[6,3]])
#lu, piv = spla.lu_factor(M_forLU1)
#print("lu =", lu)
#print("piv =", piv)
#print(mkVecByDig(6, 5))

def genGdiag_A61():
	r = mkVecByDig(6, 40)
	r[0] = 5
	r[-1] = 5
	return r

def ftDiag_A61():
	return mkVecByDig(-4, 39)

def sndDiag_A61():
	return mkVecByDig(1, 38)

#mdA61 = genGdiag_A61()
#print(mdA61.shape)

def gen0Diag(i):
	return np.array([[i, i]])

def gen1Diag(i):
	return np.array([[i, i+1], [i+1, i]])

def gen2Diag(i):
	return np.array([[i, i+2], [i+2, i]])

def gen3Diag(i):
	return np.array([[i, i+3], [i+3, i]])

def fillerMatr(Vec, indexGen, M):
	for i in range(0, len(Vec)):
		indexes = indexGen(i)
		for j in range(0, len(indexes)):
			rc = indexes[j]
			r = indexes[j][0]
			c = indexes[j][1]
			M[r][c] = Vec[i]
	return M

#d0 = np.array([4,3,2])
#d1 = np.array([5,6])
#d2 = np.array([7])
#M = np.full((3, 3), 0)
#M = fillerMatr(d0, gen0Diag, M)
#M = fillerMatr(d1, gen1Diag, M)
#M = fillerMatr(d2, gen2Diag, M)
#print(M)

def mk3DiagMatr(d0, d1, d2):
	n = len(d0)
	M = np.zeros((n, n))
	M = fillerMatr(d0, gen0Diag, M)
	M = fillerMatr(d1, gen1Diag, M)
	M = fillerMatr(d2, gen2Diag, M)
	return M

A_p61_t = mk3DiagMatr(genGdiag_A61(), ftDiag_A61(), sndDiag_A61())
#print(A_p61_t)
#detAp61_t = det(A_p61_t)
#print("detAp61_t=", detAp61_t)
#det_A_p61_o = 4.10400390 * 0.1 * np.power(2, 12)
#print("det_A_p61_o=", det_A_p61_o)
#print("delta=", deltaRel(detAp61_t, det_A_p61_o))
#
#b_p62 = mkVec_e(40, 0)
#x_p62_t = lsolve(A_p61_t, b_p62)
#print("x_p62_t=",x_p62_t)
#page 88
size_p88 = 7
def d0_Ap88():
	R = mkVecByDig(6, size_p88)
	R[0] = 5
	R[-1] = 5
	return R
#
#print(d0_Ap88())
#ftDiag_A_p88 = mkVecByDig(-4, size_p88 - 1)
#sdDiag_A_p88 = mkVecByDig(1, size_p88 - 2)
#A_p88_t = mk3DiagMatr(d0_Ap88(), ftDiag_A_p88, sdDiag_A_p88)
#print("A_p88_t=", A_p88_t)
#b_p88 = mkVec_e(size_p88, 4-1)
#print("b_p88=", b_p88)
#x_p88_t = lsolve(A_p88_t, b_p88)
#x_p88_o = np.array([4,7.5,10,11,10,7.5,4])
#print("del(x_p88_t)=", matVariation(x_p88_t, x_p88_o))
#page105
#b_p105 = mkVec_e(size_p88, 4) * 360360
#print("b_p105=", b_p105)
#x_p105_t = lsolve(G7_o, b_p105)
#print("x_p105_t=", x_p105_t)
#page 188
size_p188 = 44

def d0_p188():
	R = mkVecByDig(6, size_p188)
	R[0] = 5
	R[-1] = 5
	return R

def d1_p188():
	R = mkVecByDig(3, size_p188 - 1)
	R[0] = 2
	R[-1] = 2
	return R

d2_p188 = mkVecByDig(1, size_p188 - 2)
d3_p188 = mkVecByDig(1, size_p188 - 3)
#print("d0_p188=", d0_p188())
#
def mk4DiagMatr(d0, d1, d2, d3):
	n = len(d0)
	M = np.zeros((n, n))
	M = fillerMatr(d0, gen0Diag, M)
	M = fillerMatr(d1, gen1Diag, M)
	M = fillerMatr(d2, gen2Diag, M)
	M = fillerMatr(d3, gen3Diag, M)
	return M

B_p188 = mk4DiagMatr(d0_p188(), d1_p188(), d2_p188, d3_p188)
eigVal_188, eigVel_188 = npla.eig(B_p188)
#eigVal_188 = np.sort(eigVal_188)
#print("B_p188=", B_p188)
#w, v = npla.eig(np.diag((1, 2, 3)))
#print("eigVal_188=", eigVal_188)
#print("v=", v)

import numpy as np
from numpy import linalg as npla
#
def eigen(A):
	eigenValues, eigenVectors = npla.eig(A)
	idx = np.argsort(eigenValues)
	eigenValues = eigenValues[idx]
	eigenVectors = eigenVectors[:,idx]
	return (eigenValues, eigenVectors)
#
evs_p188 = eigen(B_p188)
evals188 = evs_p188[0]
evecs188 = evs_p188[1]
print(evecs188[:, 14])