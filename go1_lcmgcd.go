package main
import "fmt"
func main() {
 var a, b, x, y, gcd, lcm int
 fmt.Print("Enter two numbers: ")
 fmt.Scan(&a, &b)
 x = a
 y = b
 for y != 0 {
 rem := x % y
 x = y
 y = rem
 }
 gcd = x
 lcm = (a * b) / gcd
 fmt.Println(gcd, lcm)
}
