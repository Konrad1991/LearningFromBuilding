fd <- function(fct, pos, h = 1e-3, ...) {
  stopifnot("fct has to be of type function" = is.function(fct))
  stopifnot("pos has to be of type numeric" = is.numeric(pos))
  stopifnot("pos has to be at least of length one" = length(pos)>=1)
  stopifnot("h has to be of type numeric" = is.numeric(h))
  stopifnot("length(h) != 1" = length(h)==1)
  
  fct_pos <- fct(pos, ...)
  jac <- matrix(nrow = length(fct_pos), ncol = length(pos), data = 0)
  for(i in seq_along(pos)) {
    pos_new <- pos
    pos_new[i] <- pos_new[i] + h
    jac[, i] <- (fct(pos_new, ...) - fct_pos) / h
  }
  return(jac)
}

f_test <- function(pos) {
  y <- numeric(2)
  y[1] <- pos[1]^2 + pos[2]^2 + pos[3]*sin(pos[1])
  y[2] <- pos[3]^2 + pos[3]*sin(pos[2])
  return(y)
}

jac <- dfdr::jacobian(f_test, y, pos)
pos <- c(1, 2, 3)
jac(pos)
fd(f_test, pos)
jac
