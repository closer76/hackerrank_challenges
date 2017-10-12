import Data.List

checkPrime primes n = foldr (\x acc -> if n `mod` x == 0 then False else acc) True $ dropWhile (\m -> m ^ 2 > n) primes

composePrime primes n = if checkPrime primes n then (n:primes) else primes

nthPrimeImpl [] _ 0 = 1
nthPrimeImpl (p:primes) _ 0 = p
nthPrimeImpl primes x n = if checkPrime primes x then nthPrimeImpl (x:primes) (x+1) (n-1) else nthPrimeImpl primes (x+1) n

nthPrime n = nthPrimeImpl [] 2 n

primesTo m = sieve [2..m]
    where sieve [] = []
          sieve (x:xs) = x : sieve (xs \\ [x, x+x..m])

main = do
    --putStrLn . show $ nthPrime 10000
    putStrLn . show . last . take 10000 . primesTo $ 120000
