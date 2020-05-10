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
network Wireless1
{
    parameters:
        @display("bgi=background/pale,s;bgb=1200,1200");
//		@display("bgb=1200,1200");
        int noOfNodes;
        int noOfSinks;
        int noOfClusters;
        int networkRadius @unit(m);
        int txRadius @unit(m); //this is d square radius threshhold d0
    submodules:
        s[noOfSinks]: Sink;
        n[noOfNodes]: Sensor;
}
