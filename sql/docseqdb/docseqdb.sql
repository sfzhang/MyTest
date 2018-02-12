create database if not exists `docseqdb`;

use `docseqdb`;

--
-- tbl_sw_cfg
--
drop table if exists `tbl_sw_cfg`;
create table `tbl_sw_cfg` (
    `seq_year`  char(2) not null,
    `seq_month` char(1) not null,
    `seq_id`    smallint not null,
    primary key (`seq_year`, `seq_month`, `seq_id`)
);

--
-- tbl_sw_seq
--
drop table if exists `tbl_sw_seq`;
create table `tbl_sw_seq` (
    `sequence`  char(6) not null,
    `project`   char(16) not null,
    `owner`     varchar(32) not null,
    `create_ts` timestamp not null default current_timestamp on update current_timestamp,
    primary key (`sequence`),
    index idx_sw_seq_i1 (`create_ts`)
);

grant all privileges on docseqdb.* to 'doc'@'%' identified by 'doc';
