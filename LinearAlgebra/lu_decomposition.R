# aim: A = LU
# L is a lower triangle matrix --> all elements above diagonal are zero
# U is a upper triangle matrix --> all elements below diagonal are zero
LU_decomp <- function(A) {
  # Check if A is a square matrix
  if (!is.matrix(A) || nrow(A) != ncol(A)) {
    stop("Input must be a square matrix")
  }
  
  n <- nrow(A)
  L <- diag(n)
  U <- A
  
  # Perform Gaussian elimination with partial pivoting
  for (k in 1:(n - 1)) { # loop over rows
    # Find pivot element
    # index of largest abs value of kth column of U
    p <- which.max(abs(U[k:n, k]))
    p <- p + k - 1
    
    # Check for singularity
    if (U[p, k] == 0) {
      stop("Matrix is singular")
    }
    
    # Swap kth row with pth row of U
    # Swap the columns 1:(k-1) for the row c(k, p) to c(p, k)
    # thereby the largest abs value is moving to the diagonal position U[k,k]
    if (p != k) {
      U[c(k, p), ] <- U[c(p, k), ]
      L[c(k, p), 1:(k-1)] <- L[c(p, k), 1:(k-1)] 
    }
    
    # Compute multipliers and update U and L
    for (i in (k + 1):n) {
      L[i, k] <- U[i, k] / U[k, k]
      U[i, k:n] <- U[i, k:n] - L[i, k] * U[k, k:n]
    }
  }
  
  return(list(L = L, U = U))
}


# Define input matrix
A <- matrix(c(2, 1, 1, 4, 3, 3, 8, 7, 9), nrow = 3, ncol = 3)
A

# Perform LU decomposition
LU <- LU_decomp(A)

# Print the results
print(LU$L)
print(LU$U)

library(Matrix)
det(A) # -144 => matrix is not singular 
mat_lu = lu(A)
expand(mat_lu) #contains P, L, U
