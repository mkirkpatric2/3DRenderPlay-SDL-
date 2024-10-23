//
// Created by M on 10/11/2024.
//
//THESE FUNCTIONS ARE NOT INCLUDED IN THE CMAKEFILE



//SEE TWODIMMATHMANAGER and CUBE classes for full info on named data structures. In short:
//Adjacentsmap is a map where key=cornernumber value = cornerNumbersOfAdjacentCorners
//FrameCoords is map where key=coernerNumber value=coordinates AFTER projecting on 2d frame


//int findSingleAdjacent(int c1, int c2, int c3, int c4, int p){
//    if (adjacentsMap[p].a==c1 || adjacentsMap[p].b==c1 || adjacentsMap[p].c==c1) return c1;
//    if (adjacentsMap[p].a==c2 || adjacentsMap[p].b==c2 || adjacentsMap[p].c==c2) return c2;
//    if (adjacentsMap[p].a==c3 || adjacentsMap[p].b==c3 || adjacentsMap[p].c==c3) return c3;
//    if (adjacentsMap[p].a==c4 || adjacentsMap[p].b==c4 || adjacentsMap[p].c==c4) return c4;
//    return 0;
//}
//
//int findClosestNonAdjacentInSquare(int c1, int c2, int c3, int c4, int p, int p2){
//    int h1, h2, h3, h4;
//
//
//    if(p2 != c1){
//        h1 = ((frameCoords[c1].x-frameCoords[p].x)*(frameCoords[c1].x-frameCoords[p].x) +
//              (frameCoords[c1].y-frameCoords[p].y)*(frameCoords[c1].y-frameCoords[p].y));
//    } else h1 = 100000;
//
//    if(p2 != c2){
//        h2 = ((frameCoords[c2].x-frameCoords[p].x)*(frameCoords[c2].x-frameCoords[p].x) +
//              (frameCoords[c2].y-frameCoords[p].y)*(frameCoords[c2].y-frameCoords[p].y));
//    } else h2 = 100000;
//
//    if(p2 != c3){
//        h3 = ((frameCoords[c3].x-frameCoords[p].x)*(frameCoords[c3].x-frameCoords[p].x) +
//              (frameCoords[c3].y-frameCoords[p].y)*(frameCoords[c3].y-frameCoords[p].y));
//    } else h3 = 100000;
//
//    if(p2 != c2){
//        h4 = ((frameCoords[c4].x-frameCoords[p].x)*(frameCoords[c4].x-frameCoords[p].x) +
//              (frameCoords[c4].y-frameCoords[p].y)*(frameCoords[c4].y-frameCoords[p].y));
//    } else h4 = 100000;
//
//    if(h1<h2 && h1<h3 && h1<h4) return c1;
//    else if (h2<h1 && h2<h3 && h2<h4) return c2;
//    else if (h3<h1 && h3<h2 && h3 < h4) return c3;
//    else return c4;
//}



/*
 * Below is a code section I wrote while walking through the possibilities the first time. I needed to see the options.
 * I'm keeping it for reference for potential additional shapes. In essence, I was stacking triangles
 * for each "drawable corner" and checking future corners against them.
 * Cubes and rect prisms give the easy option exercised in the main program atm.
 * Oddly-shaped solids may introduce the need for some functionality or similar thought processes below
 */

//
//        int corner1, corner2, corner3;
//        //if we reach this conditional, there are exactly 3 corners.
//        // check the first entry to see if both other entries are adjacent. If so, start with entry 1. Otherwise, start with 0.
//        //corner 1 is an edge corner, corner 2 middle, corner 3 edge.
//        if(
//                (adjacentsMap[addCorners[0]].a==addCorners[1] || adjacentsMap[addCorners[0]].b==addCorners[1] || adjacentsMap[addCorners[0]].c==addCorners[1])
//                &&
//                (adjacentsMap[addCorners[0]].a==addCorners[2] || adjacentsMap[addCorners[2]].b==addCorners[2] || adjacentsMap[addCorners[2]].c==addCorners[1])
//                ){
//            corner1 = addCorners[1];
//            corner2 = addCorners[0];
//            corner3 = addCorners[2];
//        } else if (
//                (adjacentsMap[addCorners[0]].a==addCorners[1] || adjacentsMap[addCorners[0]].b==addCorners[1] || adjacentsMap[addCorners[0]].c==addCorners[1])
//                &&
//                (adjacentsMap[addCorners[1]].a==addCorners[2] || adjacentsMap[addCorners[1]].b==addCorners[2] || adjacentsMap[addCorners[1]].c==addCorners[1])
//                ){
//            corner1 = addCorners[0];
//            corner2 = addCorners[1];
//            corner3 = addCorners[2];
//        } else {
//            corner1 = addCorners[0];
//            corner2 = addCorners[2];
//            corner3 = addCorners[1];
//        }
//
//        if (c5) {
//            drawableCorners.push_back(c5);
//            //find the triangle
//            t1.a = c5;
//            t1.b = findSingleAdjacent(c1, c2, c3, c4, c5);
//
//            //dont thinkk the line below actually solves the problem.  Might have to just hceck the 2 square points adjacent to t1.b
//            t1.c = findClosestNonAdjacentInSquare(c1, c2, c3, c4, c5, t1.b);
//
//            if(c6){
//                inT1 = isWithinTriangle(frameCoords[c5], frameCoords[t1.b], frameCoords[t1.c], frameCoords[magnitudes[c6].cornerNo]);
//                if (!inT1) {
//                    drawableCorners.push_back(c6);
//                    t2.a = c6;
//                    t2.b = findSingleAdjacent(c1, c2, c3, c4, c6);
//
//
//
//                    {
//                        //if c6 is adjacent to c5 make 2 triangles - one w/ non-c5 adjacent X and the adjacent to X that is not in t1
//                        // the other with non-c5 adjacent X and c5
//                        if (adjacentsMap[c6].a == c5 || adjacentsMap[c6].b == c5 || adjacentsMap[c6].c == c5) {
//                            t2.c = c5;
//
//                            //t3
//                            t3.a = c6;
//                            t3.b = t2.b;
//
//                            // adjacent to t3.b that is not t1.b
//                            if (adjacentsMap[t3.b].a != t1.b && adjacentsMap[t3.b].a != c6) t3.c = adjacentsMap[t3.b].a;
//                            else if (adjacentsMap[t3.b].b != t1.b && adjacentsMap[t3.b].b != c6)
//                                t3.c = adjacentsMap[t3.b].b;
//                            else t3.c = adjacentsMap[t3.b].c;
//
//
//                            //At this point, there are 3 options because there can only be 6 or 7 visible corners.
//                            //1. 7 is visible and 8 is not. (elif covers)
//                            //2. 8 is visible and 7 is not  (elif covers)
//                            //3. neither is visible         (neither elif get executed)
//                            if (c7) {
//                                inT1 = isWithinTriangle(frameCoords[t1.a], frameCoords[t1.b], frameCoords[t1.c],
//                                                        frameCoords[c7]);
//                                inT2 = isWithinTriangle(frameCoords[t2.a], frameCoords[t2.b], frameCoords[t2.c],
//                                                        frameCoords[c7]);
//                                inT3 = isWithinTriangle(frameCoords[t3.a], frameCoords[t3.b], frameCoords[t3.c],
//                                                        frameCoords[c7]);
//
//                                if (!inT1 && !inT2 && !inT3) drawableCorners.push_back(c7);
//                            } else if (c8) {
//                                inT1 = isWithinTriangle(frameCoords[t1.a], frameCoords[t1.b], frameCoords[t1.c],
//                                                        frameCoords[c8]);
//                                inT2 = isWithinTriangle(frameCoords[t2.a], frameCoords[t2.b], frameCoords[t2.c],
//                                                        frameCoords[c8]);
//                                inT3 = isWithinTriangle(frameCoords[t3.a], frameCoords[t3.b], frameCoords[t3.c],
//                                                        frameCoords[c8]);
//
//                                if (!inT1 && !inT2 && !inT3) drawableCorners.push_back(c8);
//                            }
//
//
//                        } else { //triangle will be with the one adjacent in the square t2.b and t2.c is the adjacent to t2.b that is in t1
//                            t2.c = findSingleAdjacent(t1.a, t1.b, t1.c, 0, t2.b);
//
//                            if (adjacentsMap[t2.b].a != t1.b && adjacentsMap[t2.b].a != c6) t2.c = adjacentsMap[t2.b].a;
//                            else if (adjacentsMap[t2.b].b != t2.b && adjacentsMap[t2.b].b != c6)
//                                t2.c = adjacentsMap[t2.b].b;
//                            else t2.c = adjacentsMap[t2.b].c;
//                        }
//                    }
//
//                }
//            }
//        }




/* Intent:
 * Calculate the magnitudes of the 2 vectors between the non-adjacent of the 4 points
 * closest to the screen on the z axis [smallest 4 in magnitudes vector]
 * as projected onto the frame.
 *
 * Grab the 5th closest in (magnitudes). calc the distance b/w it and the 4 on the screen.
 * If any value is greater than the 2 magnitudes calculated in the last step, add to renderlist.
 *
 * If not, figure out how to check if its in that space around the shape
 * where the mag is less than the cross section but still out of bounds. If so, add.
 *
 * Otherwise move to the next closest.
 *
 * If you add a new cornerNo.... scrap this.
 *
 * Intent #2:
 * 1st check.
 * calc lines b/w adjacent first 4 corners. y=((y2-y1)/(x2-x1))x+b
 * 2 states
 * a) perfectly level. Lines are x=k, y=k
 * -- here, if x > higher of x=k or x < lower of x=k, draw and add. Same for y.
 *
 *
 * b) not level. Benefit of it just being a cube, know this won't work for other shapes.
 * --each cornerNo will either be the furthest up, right, left, down.
 * scrap that.
 **
     * Intent 3. Inefficent? But should guarantee?
     * Any point P within a triangle ABC results in
     * areaABC = aPAB+aPAC+aPBC
     *
     * Divvy the first square into 2 triangles. Grab magnitude between adjacents on frame.
     * Grab magnitude of one cross section of first 4 on frame quadrilateral.
     * calculate areas of the 2 triangles.
     *
     * Place next closest point. Determine magnitude between it and all other points.
     * if a or b, within scope and its not to be rendered.
     * a = (areaABC1 == aPAB1+aPAC1+aPBC1)
     * b = (areaABC2 = aPAB2+aPAC2+aPBC2)
     * else add to renderable.
     *
     * Calc magnitude between point and 2 closest points w/ respect to frame.
     * repeat but checking for c = (areaABC3 = aPAB3+aPAC3+aPBC3)
     *
     * Loop through entire vector.
     *
     * At each step, record drawables.
     *
     * Slight deviation if first 4 projected are in this shape

     *
     *
 */
