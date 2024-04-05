module vector

implicit none


! vector
! =======================================================================
! type vector
type :: vec
    real*8, allocatable, dimension(:) :: array
    integer :: n
contains
	procedure, public :: pv => print_vec_impl

    procedure, public :: vassign, iassign, dassign
    generic, public :: assignment(=) => vassign, iassign, dassign

    final :: destructor

end type vec

! constructor
interface vec
    module procedure constructor
end interface vec

! adding
interface operator (+)
    module procedure vadd
    module procedure vdadd
    module procedure dvadd
    module procedure vfadd
    module procedure fvadd
    module procedure viadd
    module procedure ivadd
end interface

! methods
! =======================================================================
contains

! constructor
function constructor(n) result(v)
    type(vec) :: v
    integer, intent(in) :: n
    if(.not. allocated(v%array)) then 
        allocate(v%array(n))
    else
        deallocate(v%array)
        allocate(v%array(n))
    end if
    v%n = n
end function constructor

! destructor
subroutine destructor(this)
    type(vec) :: this
    if(allocated(this%array)) then
        deallocate(this%array)
    end if
end subroutine destructor

! printing
subroutine print_vec_impl(self)
    class(vec) :: self
    print *, self%array
end subroutine print_vec_impl

! adding
function vadd(v1, v2) result (v3)
    type(vec), intent(in) :: v1, v2
    type(vec) :: v3
    v3%array = v1%array + v2%array
end function vadd

function vdadd(v1, d) result (v2)
    type(vec), intent(in) :: v1
    real*8, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + d
end function vdadd

function dvadd(d, v1) result (v2)
    type(vec), intent(in) :: v1
    real*8, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + d
end function dvadd

function vfadd(v1, d) result (v2)
    type(vec), intent(in) :: v1
    real*4, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + real(d, 8)
end function vfadd

function fvadd(d, v1) result (v2)
    type(vec), intent(in) :: v1
    real*4, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + real(d, 8)
end function fvadd

function viadd(v1, d) result (v2)
    type(vec), intent(in) :: v1
    integer, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + real(d, 8)
end function viadd

function ivadd(d, v1) result (v2)
    type(vec), intent(in) :: v1
    integer, intent(in) :: d
    type(vec) :: v2
    v2%array = v1%array + real(d, 8)
end function ivadd

! assignment
pure subroutine vassign(this, v_inp) 
    class(vec), intent(in) :: v_inp
    class(vec), intent(inout) :: this
    if(.not. allocated(this%array)) then 
        allocate(this%array(v_inp%n))
    else
        deallocate(this%array)
        allocate(this%array(v_inp%n))
    end if
    this%n = v_inp%n
    this%array = v_inp%array
end subroutine vassign

pure subroutine iassign(this, i_inp) 
    integer, intent(in) :: i_inp
    class(vec), intent(inout) :: this
    this%n = 1
    this%array = real(i_inp, 8)
end subroutine iassign

pure subroutine dassign(this, d_inp) 
    real*8, intent(in) :: d_inp
    class(vec), intent(inout) :: this
    this%n = 1
    this%array = d_inp
end subroutine dassign

end module vector



program main
	use vector
	implicit none

    type(vec) :: v1, v2, v3
    real*8 :: d
    integer :: i
	v1 = vec(5)
    v2 = vec(5)
    v2 = 3
    v1 = 5
    v3 = v1 + v2

    d = 3.14
    v1 = d + v2 + d
    
    i = 3
    v1 = i + v1 + i*2

    v1 = v1 + 3

    v1 = v1 + 4.5

	call v1%pv()
    call v2%pv()
    call v3%pv()

end program




