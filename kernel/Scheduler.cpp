/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    //return m_queue.count();
    return m_queue5.count() + m_queue4.count() + m_queue3.count() + m_queue2.count() + m_queue1.count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }
    int prio = proc->getPriority();
    if (prio == 1){
        m_queue1.push(proc);
    }
    else if (prio == 2){
        m_queue2.push(proc);
    }
    else if (prio == 3){
        m_queue3.push(proc);
    }
    else if (prio == 4){
        m_queue4.push(proc);
    }
    else if (prio == 5){
        m_queue5.push(proc);
    }
    else {
        ERROR("Unknown priority: " << prio << ", failed to enqueue");
        return InvalidArgument;
    }
    return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }
    //MODIFIED DEQUEUE
    int prio = proc->getPriority();
    Size count;
    switch(prio){
        case 1:
            count = m_queue1.count();
            for (Size i = 0; i < count; i++)
            {
                Process *p = m_queue1.pop();

                if (p == proc)
                    return Success;
                else
                    m_queue1.push(p);
            }
            FATAL("process ID " << proc->getID() << " is not in the schedule 1");
            return InvalidArgument;
            break;
        case 2:
            count = m_queue2.count();
            for (Size i = 0; i < count; i++)
            {
                Process *p = m_queue2.pop();

                if (p == proc)
                    return Success;
                else
                    m_queue2.push(p);
            }
            FATAL("process ID " << proc->getID() << " is not in the schedule 2");
            return InvalidArgument;
            break;
        case 3:
            count = m_queue3.count();
            for (Size i = 0; i < count; i++)
            {
                Process *p = m_queue3.pop();

                if (p == proc)
                    return Success;
                else
                    m_queue3.push(p);
            }
            FATAL("process ID " << proc->getID() << " is not in the schedule 3");
            return InvalidArgument;
            break;
        case 4:
            count = m_queue4.count();
            for (Size i = 0; i < count; i++)
            {
                Process *p = m_queue4.pop();

                if (p == proc)
                    return Success;
                else
                    m_queue4.push(p);
            }
            FATAL("process ID " << proc->getID() << " is not in the schedule 4");
            return InvalidArgument;
        case 5:
            count = m_queue5.count();
            for (Size i = 0; i < count; i++)
            {
                Process *p = m_queue5.pop();

                if (p == proc)
                    return Success;
                else
                    m_queue5.push(p);
            }
            FATAL("process ID " << proc->getID() << " is not in the schedule 5");
            return InvalidArgument;
            break;
        default:
            FATAL("process ID " << proc->getID() << " is not in the schedule (default)");
            return InvalidArgument;
            break;
    }
    FATAL("process ID " << proc->getID() << " is not in the schedule (outside switch statement)");
    return InvalidArgument;
    
    //ORIGINAL CODE
    //Size count = m_queue.count();
    

    // // Traverse the Queue to remove the Process
    // for (Size i = 0; i < count; i++)
    // {
    //     Process *p = m_queue.pop();

    //     if (p == proc)
    //         return Success;
    //     else
    //         m_queue.push(p);
    // }

    // FATAL("process ID " << proc->getID() << " is not in the schedule");
    // return InvalidArgument;
}

Process * Scheduler::select()
{
    //ORIGINAL CODE
    // if (m_queue.count() > 0)
    // {
    //     Process *p = m_queue.pop();
    //     m_queue.push(p);

    //     return p;
    // }

    //MODIFIED SELECT
    if (m_queue5.count() > 0)
    {
        Process *p = m_queue5.pop();
        m_queue5.push(p);

        return p;
    }
    else if (m_queue4.count() > 0)
    {
        Process *p = m_queue4.pop();
        m_queue4.push(p);

        return p;
    }
    else if (m_queue3.count() > 0)
    {
        Process *p = m_queue3.pop();
        m_queue3.push(p);

        return p;
    }
    else if (m_queue2.count() > 0)
    {
        Process *p = m_queue2.pop();
        m_queue2.push(p);

        return p;
    }
    else if (m_queue1.count() > 0)
    {
        Process *p = m_queue1.pop();
        m_queue1.push(p);

        return p;
    }

    return (Process *) NULL;
}
