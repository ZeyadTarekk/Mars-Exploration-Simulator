
# __Mars station__

## **Content**
1. ## Contributers
2. ## Description
3. ## Project Summary
4. ## Chosen data structures
5. ## Justification

## **Contributers**

| Abdelrahman Mohamed | Mohamed Nabil | Ziad Sherif | Ziad Tarek |
| :-----------------: | :-----------: | :---------: | :--------: |

## **Description**

* In the hope of getting to know more about Mars and the possibility of life on its surface, a huge number of exploratory missions to different regions of the planet need to be conducted. Imagine (at some future time) that we have several rovers of different types and capabilities on the surface of Mars ready to carry out missions to its different regions. There is also a hypothetical base station which acts as the central point from which the different rovers begin their exploratory missions and to which they return after mission completion. The base station basically assigns missions to the different rovers.
* Using our programming skills and our knowledge of the different data structures, we are going to develop a program that simulates the mission assignment process and calculates some related statistics in order to help improve the overall process.

## **Project-Summary**

* We have a some missions on mars that we should try to complete them with best perfomance.
*  The missions should be assigned to some rovers in mars station 
* ###  **Missions** : -
    * **Formulation Day**: the day when the mission formulation is finalized and the mission becomes ready to be assigned to a rover. 
    * **Type**: There are _3 types_ of missions: Emergency, Mountainous and Polar missions. 
        * _Emergency missions_ must be assigned first before mountainous and polar missions. 
        * _Mountainous_ missions are missions to mountainous regions of Mars and must be conducted by rovers equipped to navigate in such regions. 
        * _Polar_ missions are missions to the polar ice caps of Mars and must be conducted by rovers equipped to navigate in such regions. 
    * **Target Location**: The distance (in kilometers) from the base station to the target location of the mission. 
    * **Mission Duration**: The number of days needed to fulfill the mission requirements at the target location. 
    * **Significance**: A number representing the importance of the mission and how beneficial it is (the higher the number, the more significant it is).

* ### **Rover** : -
    * **Rover Type**: There are _3 types_ of rovers: Emergency rovers, Mountainous rovers, and Polar rovers. 
        * _Emergency_ rovers are rovers which are over-equipped and ready for emergency missions in almost any region. 
        * _Mountainous_ rovers are rovers which can navigate in mountainous regions. 
        * _Polar_ rovers are rovers which can navigate in polar regions.  
    * **Checkup Duration**: The duration (in days) of checkups that a rover needs to perform after completing N missions. 
    * **Speed**: in kilometers/hour. (Note that a day on Mars is 25 hours.)
* ### **Missions Assignment Criteria** : -
    * First, assign emergency missions to ANY emergancy available rover if there is no emergency rovers try to assign the mission to any mountainous available rover if there is no mountainous rover try to assign the mission to any polar available rover. 
    * polar missions assigned using the available polar rovers ONLY. 
    * mountainous missions assigned using mountainous then emergency rovers.
* ### **Events** : -
    1. _Formulation_ : -
        * This event occurs when a mission reaches to the mars station to be executed.
    2. _Assign_ : - 
        * We execute this event when we want to assign a mission to a rover.
    3. _Complete_ : -
        * We execute this event to organize mission completion and rovers checkup completion 
    4. _Promotion_ : -
        * this event is executed when an order reaches to mars station to promote mountainous mission to emergency mission.
    5. _Cancelation_ : -
        * this event is executed when an order reaches to mars station to cancel a mountainous event.
    6. _Auto Promotion_ : -
        * this event is executed when a mountainous mission waits for a certain limit which is an alert to promote this mission to emergency one.
    7. _Mission failure_ : - 
        * this event tries to make the simulation similar to reality as possible in which a mission may fail with unexpected reasons.

## **Chosen data structures**

| List Name                                 | Chosen Data structure | 
| :----------------------:                  | :-------------------: | 
|Emergency waiting missions                 | Priority queue        |
|Mountainous waiting missions               | List                  |
|Polar waiting missions                     | Queue                 |
|Completed missions                         | Queue                 |
|Execution (In-service) missions            | Priority queue        |
|Available emergency rovers                 | Priority queue        |
|Available Mountainous rovers               | Priority queue        |
|Available polar rovers                     | Priority queue        |
|Event list                                 | Queue                 |
|Unavailable rovers                         | Priority queue        |
|unAvailableMaintainanceEmergency rovers    | List                  |
|unAvailableMaintainanceMountainous rovers  | List                  |
|unAvailableMaintainancePolar rovers        | List                  |


## **Justification**
1. _Emergency waiting missions_ : -
    
    * **Operations**: -

            1-	Dequeue and enqueue according to priority O(1)

    * **Description**: -
    
            This list contains Emergency missions that wait for rovers to be executed.

    * **Justification**: -
    
            Emergency waiting missions should be assigned according to their priority.
2. _Mountainous waiting missions_ : -
    * **Operations**: -

            1-	Remove from the beginning O(1)

            2-	insert from the end O(N) or using tail O(1) 

            3-	Promotion and Cancelation (Search) O(N)

            4-	Auto promotion O(1)

    * **Description**: -
    
            This list contains Mountainous missions that wait for rovers to be executed.
    
    * **Justification**: -
        
            Mountainous missions have some operations which requires search like cancelation and promotion, also we need to keep the sequence of the missions in the input file so that first come first served, list is suitable for that it has search method and during using it we would handle their sequence (remove from the beginning and insert from the end). 

3. _Polar waiting missions_ : -

    * **Operations**: -
            
            1- First-come first-served (Dequeue and enqueue) O(1)

    * **Description**: -
            
            This list contains Polar missions that wait for rovers to be executed.

    * **Justification**: -
            
            Polar waiting missions should be assigned according to their formulation date (First-come-first-served) 

4. _Completed missions_ :-

    * **Operations**: -

            1- Printing missions in the output file O(N)

            2- Dequeue O(1)

            3- Enqueue O(1)

    * **Description**: -
        
            This list contains all completed missions of any type.

    * **Justification**: -

            We need only to keep this list for printing after each day and printing them in the output file.

5. _Execution (In-service) missions_ : -

    * **Operations**: -
            
            1- Dequeue and enqueue according to Time O(1)

    * **Description**: -
            
            This list contains all missions of any type which still in the execution period.

    * **Justification**: -
            
            These missions should be sorted according to completion time.
            Missions would be removed according to completion time.

6. _Available emergency rovers_ : -

    * **Operations**: -
        
            1- Dequeue and enqueue according to speed O(1)

    * **Description**: -

            This list contains Available emergency rovers.

    * **Justification**: -
            
            Rovers should be sorted according to their speed to assign missions to faster rovers first.

            Available rovers’ lists are separated into three lists so that no search operations are needed every time we need to assign a mission.
7. _Available Mountainous rovers_ : -
    
    * **Operations**: -
        
            1- Dequeue and enqueue according to speed  O(1)

    * **Description**: -
            
            This list contains Available Mountainous rovers.

    * **Justification**: -

            Rovers should be sorted according to their speed to assign missions to faster rovers first.
8. _Available polar rovers_ : -

    * **Operations**: -
        
            1- Dequeue and enqueue according to speed O(1)

    * **Description**: -

            This list contains Available polar rovers.

    * **Justification**: -
            
            Rovers should be sorted according to their speed to assign missions to faster rovers first.

9. _Event list_ : -
    
    * **Operations**: -
        
            1- Dequeue and enqueue according to assigning time O(1)

    * **Description**: -
            
            This list contains all needed events.

    * **Justification**: -
            
            The event list should be executed according to their order in the input file.

10. _Unavailable rovers_ :-

    * **Operations**: -

            1- Dequeue and enqueue according to time of mission completion and checkup end O(1)

    * **Description**: -
            
            This list should contain all unavailable rovers of any type and of any status either it is in checkup or its in-service.

    * **Justification**: -
            
            Unavailable rovers should be stored according to the time at which each rover completes its mission and according to the time at which the rovers in checkup status finish their checkup.
            We decided to make it one list for in-service and checkup because there is no difference between them in either case, they would be unavailable and there is no operation requires to separate them.

11. _unAvailableMaintainancePolar, unAvailableMaintainanceMountainous &unAvailableMaintainanceEmergency_ : -

    * **Operations**: -

            1- Searching O(N)

    * **Description**: -
            
            This list should contain all unavailable rovers which are in maintainance.

    * **Justification**: -
            
            Rovers that are in maintainance are considered unavailable unless we have no rovers left.
            When we need to assign these rovers we need to search for the fastest rover so that we get best performance.
