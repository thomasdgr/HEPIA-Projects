use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use crate::trips::Trips;

#[derive(Debug)]
pub struct Calendar {
    pub service_id: String,
    pub monday: String,
    pub tuesday: String,
    pub wednesday: String,
    pub thursday: String,
    pub friday: String,
    pub saturday: String,
    pub sunday: String,
    pub start_date: String,
    pub end_date: String
}

impl From<&Vec<String>> for Calendar {
    fn from(v: &Vec<String>) -> Self {
        Calendar { 
            service_id:v[0].to_owned(),
            monday:v[1].to_owned(),
            tuesday:v[2].to_owned(),
            wednesday:v[3].to_owned(),
            thursday:v[4].to_owned(),
            friday:v[5].to_owned(),
            saturday:v[6].to_owned(),
            sunday:v[7].to_owned(),
            start_date:v[8].to_owned(),
            end_date:v[9].to_owned() }
    }
}

impl fmt::Display for Calendar {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\"",
            self.service_id, 
            self.monday, 
            self.tuesday, 
            self.wednesday, 
            self.thursday, 
            self.friday, 
            self.saturday, 
            self.sunday, 
            self.start_date, 
            self.end_date)
    }
}

impl PartialEq for Calendar {
    fn eq(&self, other: &Calendar) -> bool {
        self.service_id.eq(&other.service_id) && 
        self.monday.eq(&other.monday) &&
        self.tuesday.eq(&other.tuesday) &&
        self.wednesday.eq(&other.wednesday) &&
        self.thursday.eq(&other.thursday) &&
        self.friday.eq(&other.friday) &&
        self.saturday.eq(&other.saturday) &&
        self.sunday.eq(&other.sunday) &&
        self.start_date.eq(&other.start_date) &&
        self.end_date.eq(&other.end_date)
    }
}

impl Calendar {
    /// Return an option on a vector of Calendar created from a file and a vector of Trips
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    ///use gtfs::Calendar::*;
    /// 
    ///let calendar = read_calendar(&trips_vec, "./tpg_input/calendar.txt".to_string()).unwrap();
    /// 
    ///let header = "service_id,monday,tuesday,wednesday,thursday,friday,saturday,sunday,start_date,end_date";
    ///write_content(&calendar, "./tpg_output/calendar.txt", header);
    /// ```
    pub fn read_calendar(trips: &[Trips], path: String) -> Option<Vec<Calendar>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut calendar = reader.lines()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                trips.iter()
                    .filter(|trip| v[0] == trip.service_id)
                    .map(|_service_id| Calendar::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        calendar.dedup();
        Some(calendar)
    }
}