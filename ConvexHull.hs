import Text.Printf
import Data.List
import Data.Ord

type Point = (Int, Int)

-- Test data
--l :: [Point]
--l = [(1,1),(2,5),(3,3),(5,3),(3,2),(2,2)]

mapTuple f (a1, a2) = (f a1, f a2)

cross :: Point -> Point -> Point -> Int
cross o a b = (xa - xo) * (yb - yo) - (ya - yo) * (xb - xo)
    where (xo, yo) = o
          (xa, ya) = a
          (xb, yb) = b

distToLine :: Point -> Point -> Point -> Double
distToLine p1 p2 p0 = (abs ((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1)) / (sqrt ((y2 - y1) ** 2 + (x2 - x1) ** 2))
    where (x1, y1) = mapTuple fromIntegral p1
          (x2, y2) = mapTuple fromIntegral p2
          (x0, y0) = mapTuple fromIntegral p0

distance :: Point -> Point -> Double
distance p1 p2 = sqrt ((x2 - x1) ** 2 + (y2 - y1) ** 2)
    where (x1, y1) = mapTuple fromIntegral p1
          (x2, y2) = mapTuple fromIntegral p2

recurFunc :: Point -> Point -> [Point] -> [Point]
recurFunc _ _ [] = []
recurFunc lpoint rpoint points = (recurFunc lpoint newpoint leftpoints) ++ [newpoint] ++ (recurFunc newpoint rpoint rightpoints)
    where newpoint = maximumBy (comparing $ distToLine lpoint rpoint) points
          (leftpoints, remainpoints) = partition (\a -> cross lpoint newpoint a > 0) $ delete newpoint points
          rightpoints = filter (\a -> cross newpoint rpoint a > 0) remainpoints

totalDist :: [Point] -> Double
totalDist [] = 0
totalDist (_:[]) = 0
totalDist (x1:x2:xs) = (distance x1 x2) + (totalDist $ x2:xs)

solve :: [Point] -> Double
solve points = totalDist result_points
    where lpoint = maximumBy (comparing fst) points
          rpoint = minimumBy (comparing fst) points
          (uppoints, downpoints) = partition (\a -> cross lpoint rpoint a > 0) $ points \\ [lpoint, rpoint]
          result_points = [lpoint] ++ (recurFunc lpoint rpoint uppoints) ++ [rpoint] ++ (recurFunc rpoint lpoint downpoints) ++ [lpoint]

main :: IO ()
main = do
  n <- readLn :: IO Int
  content <- getContents
  let  
    points = map (\[x, y] -> (x, y)). map (map (read::String->Int)). map words. lines $ content
    ans = solve points
  printf "%.1f\n" ans

