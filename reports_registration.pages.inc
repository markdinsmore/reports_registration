<?php
/**
 * Created by PhpStorm.
 * User: markdinsmore, dennis bennett
 * Date: 3/17/16
 * Time: 7:26 PM
 *
 * @return string Course listing for the instructor reports
 */

function course_list()
{
  global $user;

  $header = array(
	array('data' => t('Report by CRN'), 'field' => 'i.crn', 'sort' => 'desc'),
	array('data' => t('Instructor'), 'field' => 'i.instructor_name', 'sort' => 'desc',),
	array('data' => t('Course Name'), 'field' => 'i.course_name', 'sort' => 'desc',),
	array('data' => t('Section Number'), 'field' => 'i.section_number', 'sort' => 'desc',),
	array('data' => t('Term'), 'field' => 'i.term', 'sort' => 'desc',),
  );

  $courses = db_select('OSU_Registration_Instructor_Input', 'i');
  $courses->fields('i', array('crn', 'instructor_name', 'course_name', 'section_number', 'term'));
  $courses->addTag('node access');
  $courses->condition('i.onid', $user->name, '=');

  $table_sort = $courses->extend('TableSort')
	->orderByHeader($header); //then use an extender to create the sorted table
  $pager = $table_sort->extend('PagerDefault')
	->limit(20);    //take the sorted table and extend that with a pager
  $result = $pager->execute(); // execute the result
  $rows[] = array();
  foreach ($result as $row) { // add the data
	$crn = $row->crn;
	$courseName = $row->course_name;
	$sectionNumber = $row->section_number;
	$instructorName = $row->instructor_name;
	$term = $row->term;

	$form = "<form name=\"courses\" action=\"http://tac-dev.nws.oregonstate.edu/W365_reporting/course_report.php\" method=\"post\">" .
	  "<input type=\"hidden\" name=\"crs_crn\" value=\"".$crn."\">" .
	  "<input type=\"hidden\" name=\"crs_name\" value=\"".$courseName."\">" .
	  "<input type=\"hidden\" name=\"crs_section\" value=\"".$sectionNumber."\">" .
	  "<input type=\"hidden\" name=\"crs_instructor\" value=\"".$instructorName."\">" .
	  "<input type=\"hidden\" name=\"crs_term\" value=\"$term\">" .
	  "<input type=\"submit\" value=\"View ". $crn . "\">" .
	  "</form>";
	$rows[$crn]['crn'] = $form;
	$rows[$crn]['instructor_name'] = $row->instructor_name;
	$rows[$crn]['course_name'] = $row->course_name;
	$rows[$crn]['section_number'] = $row->section_number;
	$rows[$crn]['term'] = $row->term;
  }

  $build = "<p>The following are your courses registered with the Write 365 application (across all terms).</p>
                <p>Note: Columns are sortable. Click on the column heading to change the sort order.</p>";
  $build .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table')));
  $build .= theme('pager');

  return $build; // done

}


/**
 * @return string Course listing for the instructor reports
 */
function adm_courses_list()
{
  global $user;

  $header = array(
	array('data' => t('Report by CRN'), 'field' => 'i.crn', 'sort' => 'desc'),
	array('data' => t('Instructor'), 'field' => 'i.instructor_name', 'sort' => 'desc',),
	array('data' => t('Course Name'), 'field' => 'i.course_name', 'sort' => 'desc',),
	array('data' => t('Section Number'), 'field' => 'i.section_number', 'sort' => 'desc',),
	array('data' => t('Term'), 'field' => 'i.term', 'sort' => 'desc',),
  );

  $courses = db_select('OSU_Registration_Instructor_Input', 'i');
  $courses->fields('i', array('crn', 'instructor_name', 'course_name', 'section_number', 'term'));
  $courses->addTag('node access');
  $table_sort = $courses->extend('TableSort')
	->orderByHeader($header); //then use an extender to create the sorted table
  $pager = $table_sort->extend('PagerDefault')
	->limit(20);    //take the sorted table and extend that with a pager
  $result = $pager->execute(); // execute the result
  $rows[] = array();
  foreach ($result as $row) { // add the data
	$crn = $row->crn;
	$courseName = $row->course_name;
	$sectionNumber = $row->section_number;
	$instructorName = $row->instructor_name;
	$term = $row->term;
	/*$form = "<form name=\"courses\" action=\"http://tac-dev.nws.oregonstate.edu/W365_reporting/course_report.php\" method=\"post\">" .*/
	$form = "<form name=\"courses\" action=\"detail\" method=\"post\">" .
	  "<input type=\"hidden\" name=\"crs_crn\" value=\"".$crn."\">" .
	  "<input type=\"hidden\" name=\"crs_name\" value=\"".$courseName."\">" .
	  "<input type=\"hidden\" name=\"crs_section\" value=\"".$sectionNumber."\">" .
	  "<input type=\"hidden\" name=\"crs_instructor\" value=\"".$instructorName."\">" .
	  "<input type=\"hidden\" name=\"crs_term\" value=\"$term\">" .
	  "<input type=\"submit\" value=\"View ". $crn . "\">" .
	  "</form>";
	$rows[$crn]['crn'] = $form;
	$rows[$crn]['instructor_name'] = $row->instructor_name;
	$rows[$crn]['course_name'] = $row->course_name;
	$rows[$crn]['section_number'] = $row->section_number;
	$rows[$crn]['term'] = $row->term;
  }

  $build = "<p>The following are your courses registered with the Write 365 application (across all terms).</p>
<p>Note: Columns are sortable. Click on the column heading to change the sort order.</p>";
  $build .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table')));
  $build .= theme('pager');

  return $build; // done

}

function adm_course_detail()
{

  global $user;
// First the $_POST vars
  $crs_crn = htmlentities($_POST['crs_crn']);
  $crs_name = htmlentities($_POST['crs_name']);
  $crs_section = htmlentities($_POST['crs_section']);
  $crs_instructor = htmlentities($_POST['crs_instructor']);
  $term = htmlentities($_POST['crs_term']);
  $title= $crs_name."-".$crs_section."-".$crs_crn."-".$term."-".$crs_instructor."-".date('Y-m-d H:i:s');

  $build = "<p>Course Detail: " . $title . "</p>";
  $build .= "<p>Term: " . $term ."</p>";
  $build .= "<p>CRN: " . $crs_crn ."</p>";

  $header = array(
	array('data' => 'Student ID', 'field' => 'student_id', 'sort' => 'desc'),
	array('data' => 'ONID', 'field' => 'onid', 'sort' => 'desc',),
	array('data' => 'Last Name', 'field' => 'last_name', 'sort' => 'desc',),
	array('data' => 'First Name', 'field' => 'first_name', 'sort' => 'desc',),
	array('data' => 'Email', 'field' => 'email', 'sort' => 'desc',),
	array('data' => 'Status', 'field' => 'registration_status', 'sort' => 'desc',),
	//array('data' => 'UID', 'field' => 'uid', 'sort' => 'desc',),
	//array('data' => 'Name', 'field' => 'name', 'sort' => 'desc',),
  );

  $result = db_select('OSU_Registration_Student_Input', 's')->extend('PagerDefault')->limit(30);
  $result->fields('s', array('student_id','onid','last_name','first_name', 'email', 'registration_status'))
	->fields('u',array('uid', 'name'))
	->condition('term', $term)
	->condition('crn', $crs_crn)
	->addTag('node_access');
  $result->join('users','u', 's.onid = u.name');
  $result->extend('TableSort')
	->orderByHeader($header); //then use an extender to create the sorted table

  $results = $result->execute();

  $rows = array();

  foreach ($results as $row) {
	$student_id = $row->student_id;
	$onid = $row->onid;
	$last_name = $row->last_name;
	$first_name = $row->first_name;
	$email = $row->email;
	$registration_status = $row->registration_status;
	$uid = $row->uid;
	$name = $row->name;
	$form = "<form name=\"student\" action=\"student-detail\" method=\"post\">" .
	  "<input type=\"hidden\" name=\"student_id\" value=\"".$student_id."\">" .
	  "<input type=\"submit\" value=\"View ". $student_id . "\">" .
	  "</form>";
	//echo $student_id, $onid, $last_name, $first_name, $email, $registration_status, $uid, $name . "<br>";
	$rows[] = array(
	  "student_id" => $form,
	  "onid" => $onid,
	  "last_name" => $last_name,
	  "first_name" => $first_name,
	  "email" =>$email,
	  "registration_status" => $registration_status,
	  //"uid" => $uid,
	  //"name" => $name,
	);
  }

  $build .= theme('table', array('header' => $header, 'rows' => $rows));
  $build .= theme('pager');

  return $build;
}

function adm_student_detail() {
  /*
   * This is the report for an individual student.
   * Inputs: uid, first_name, email, onid
   */

}