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
	array(
	  'data' => t('Report by CRN'),
	  'field' => 'i.crn',
	  'sort' => 'desc'
	),
	array(
	  'data' => t('Instructor'),
	  'field' => 'i.instructor_name',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Course Name'),
	  'field' => 'i.course_name',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Section Number'),
	  'field' => 'i.section_number',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Term'),
	  'field' => 'i.term',
	  'sort' => 'desc',
	),
  );

  $courses = db_select('OSU_Registration_Instructor_Input', 'i');
  //$courses->join('OSU_Reports_Registration', 'r', 'i.term = r.currentterm');
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
  // and then theme in the same order.
  // first, theme the table
  // and then theme the pager.
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
	array(
	  'data' => t('Report by CRN'),
	  'field' => 'i.crn',
	  'sort' => 'desc'
	),
	array(
	  'data' => t('Instructor'),
	  'field' => 'i.instructor_name',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Course Name'),
	  'field' => 'i.course_name',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Section Number'),
	  'field' => 'i.section_number',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Term'),
	  'field' => 'i.term',
	  'sort' => 'desc',
	),
  );

  $courses = db_select('OSU_Registration_Instructor_Input', 'i');
//$courses->join('OSU_Reports_Registration', 'r', 'i.term = r.currentterm');
  $courses->fields('i', array('crn', 'instructor_name', 'course_name', 'section_number', 'term'));
  $courses->addTag('node access');
//$courses->condition('i.onid', $user->name, '=');

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
// and then theme in the same order.
// first, theme the table
// and then theme the pager.
  $build = "<p>The following are your courses registered with the Write 365 application (across all terms).</p>
<p>Note: Columns are sortable. Click on the column heading to change the sort order.</p>";
  $build .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table')));
  $build .= theme('pager');

  return $build; // done

}

function adm_course_detail()
{
  //return 'This feature not yet implemented (build 20150927).';
  //first we will return a student list for a given crn
  //then we'll add student deta


  global $user;
  // let's make a table of courses for a fixed term/ uid first
  // We're gonna need some stuff
  // First the $_POST vars
  $crs_crn = htmlentities($_POST['crs_crn']);
  $crs_name = htmlentities($_POST['crs_name']);
  $crs_section = htmlentities($_POST['crs_section']);
  $crs_instructor = htmlentities($_POST['crs_instructor']);
  $term = htmlentities($_POST['crs_term']);
  $title= $crs_name."-".$crs_section."-".$crs_crn."-".$term."-".$crs_instructor."-".date('Y-m-d H:i:s');
  $crn = $crs_crn;

  $build = "<p>Course Detail: " . $title . "</p>";
  $build .= "<p>Term: " . $term ."</p>";
  $build .= "<p>CRN: " . $crs_crn ."</p>";

  $header = array(
	array(
	  'data' => t('Student ID'),
	  'field' => 'student_id',
	  'sort' => 'desc'
	),
	//array('data' => t('Drupal UID'), 'field' => 'u.uid', 'sort' => 'desc',),
	array(
	  'data' => t('ONID'),
	  'field' => 'onid',
	  'sort' => 'desc',
	),
	array(
	  'data' => t('Last Name'),
	  'field' => 'last_name',
	  'sort' => 'desc',
	),
	array('data' => t('First Name'),
	  'field' => 'first_name',
	  'sort' => 'desc',
	),
	array('data' => t('Email'),
	  'field' => 'email',
	  'sort' => 'desc',
	),
	array('data' => t('Status'),
	  'field' => 'registration_status',
	  'sort' => 'desc',
	),
  );

  /*    $query_students = "SELECT s.student_id, u.uid, s.onid, s.last_name, s.first_name, s.email, s.registration_status
						FROM w365prod_OSU_Registration_Student_Input s
						inner join w365prod_users u on s.onid = u.name
						WHERE crn=".$crs_crn."
						AND term=".$term."
						ORDER BY s.last_name";
  */
  $result = db_select('OSU_Registration_Student_Input', 's')->extend('PagerDefault')->limit(10);

  $result->fields('s', array('student_id','onid','last_name','first_name', 'email', 'registration_status'))
	->fields('u',array('uid', 'name'))
	->condition('term', $term)
	->condition('crn', $crs_crn)
	->addTag('node_access');
  $result->join('users','u', 's.onid = u.name');
  $result->extend('TableSort')
	->orderByHeader($header); //then use an extender to create the sorted table

  $results = $result->execute();
  var_dump($results);
  $rows = array();
  foreach ($results as $row) { // add the data
	$student_id = $row->student_id;
	$onid = $row->onid;
	$last_name = $row->last_name;
	$first_name = $row->first_name;
	$email = $row->email;
	$registration_status = $row->registration_status;
	$form = "<form name=\"courses\" action=\"detail\" method=\"post\">" .
	  "<input type=\"hidden\" name=\"onid\" value=\"".$student_id."\">" .
	  "</form>";
	$rows[$crn]['student_id'] = $student_id;
	$rows[$crn]['onid'] = $onid;
	$rows[$crn]['last_name'] = $last_name;
	$rows[$crn]['first_name'] = $first_name;
	$rows[$crn]['email'] = $email;
	$rows[$crn]['registration'] = $registration_status;
  }
  var_dump($rows);
  $build .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table')));
  //$build .= theme('pager');
  return $build;
}

