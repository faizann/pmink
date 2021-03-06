/*
 * This file is part of Project MINK <http://www.release14.org>.
 *
 * Copyright (C) 2012 Release14 Ltd.
 * http://www.release14.org/
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
 *
 */

#include <sgn_stats.h>

// SgnStatsHandler
sgn::SgnStatsHandler::SgnStatsHandler(pmink_utils::StatsManager* _stats, uint32_t _id): stats(_stats), id(_id){}



void sgn::SgnStatsHandler::run(){
    value = stats->get(id);

}

// PCAPStatsHandlerRX
sgn::PCAPStatsHandlerRX::PCAPStatsHandlerRX(int _sd_id): sd_id(_sd_id){
    bzero(&stats, sizeof(stats));
}



void sgn::PCAPStatsHandlerRX::run(){
    PMPcap::getStats(sd_id, &stats);
    #ifdef __PFRING__
    value = stats.recv;
    #else
    value = stats.ps_recv;
    #endif
}

// PCAPStatsHandlerDROP
sgn::PCAPStatsHandlerDROP::PCAPStatsHandlerDROP(int _sd_id): sd_id(_sd_id){
    bzero(&stats, sizeof(stats));
}



void sgn::PCAPStatsHandlerDROP::run(){
    PMPcap::getStats(sd_id, &stats);
    #ifdef __PFRING__
    value = stats.drop;// + stats.droppedbyfilter;
    #else
    value = stats.ps_drop + stats.ps_ifdrop;
    #endif
}
