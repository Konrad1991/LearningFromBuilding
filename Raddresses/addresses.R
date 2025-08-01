same_object <- function(a, b) {
  tracemem(a) == tracemem(b)
}

a <- 1
b <- 1
same_object(a, b)
same_object(a, a)
b <- a
same_object(a, b)
