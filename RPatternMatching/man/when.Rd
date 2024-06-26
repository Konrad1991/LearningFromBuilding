% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/PatternMatching.R
\name{when}
\alias{when}
\title{Pattern matching using instances of Match}
\usage{
when(value, test, predicate, apply = FALSE)
}
\arguments{
\item{value}{An R object to be matched}

\item{test}{A condition (either a function or a direct value) to test against `value`}

\item{predicate}{A value or function to be returned or applied when `test` matches `value`}

\item{apply}{Logical, indicating whether to apply `predicate` to `value` if `predicate` is a function}
}
\description{
This function takes instances of the Match class and checks for a specific matching case based on provided conditions.
}
\details{
The `test` parameter can be:
  - A function: If `test(value)` returns TRUE, `predicate` is returned or applied to `value` (if `apply` is TRUE).
  - A direct value: If `value` matches `test`, `predicate` is returned or evaluated.

The `predicate` parameter can be:
  - A value: Directly returned when `test` matches `value`.
  - A function: Applied to `value` (if `apply` is TRUE) when `test` matches `value`.
}
\examples{
result <- Match("+") |>
  when("-", "minus") |>
  when(is.numeric, "numeric") |> 
  when(is.character, "character") |> 
  when(NULL, "not found")
print(result)

result <- Match(1L) |>
  when("-", "minus") |>
  when(is.character, "character") |> 
  when(NULL, "not found")
print(result)

}
