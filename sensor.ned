// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
// 
// TODO auto-generated type
// 
simple Sensor
{
    parameters:
    
    int clusterId = 0;
//    int chId = -1;
//    int relayId;
//    int hopCount;
        
     @display("i=misc/node2_vs");
     double x @unit(m);                 // the x coordinate of the host
     double y @unit(m);                 // the y coordinate of the host
     double energy @unit(J);
     
     gates:
         input in @directIn;
}
