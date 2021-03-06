<?php
// DWSIM Flowsheet display completed proposals
function dwsim_flowsheet_completed_proposals_all()
{
	$output = "";
	$query = db_select('dwsim_flowsheet_proposal');
	$query->fields('dwsim_flowsheet_proposal');
	$query->condition('approval_status', 3);
	//$query->condition('is_completed', 1);
	$result = $query->execute();
	if ($result->rowCount() == 0)
	{
		$output .= "Work has been completed for the following flowsheets under Flowsheeting Project<hr>";
	} //$result->rowCount() == 0
	else
	{
		$output .= "Work has been completed for the following flowsheets under Flowsheeting Project <hr>";
		$preference_rows = array();
		$i = 1;
		while ($row = $result->fetchObject())
		{
			$approval_date = date("Y", $row->approval_date);
			$preference_rows[] = array(
				$i,
				l($row->project_title, "flowsheeting-project/dwsim-flowsheet-run/" . $row->id),
				$row->university,
				$approval_date
			);
			$i++;
		} //$row = $result->fetchObject()
		$preference_header = array(
			'No',
			'Flowsheet Project',
			'Institute',
			'Year'
		);
		$output .= theme('table', array(
			'header' => $preference_header,
			'rows' => $preference_rows
		));
	}
	return $output;
}
// DWSIM Flowsheet display in progress proposals
function dwsim_flowsheet_progress_all()
{
	$page_content = "";
	$query = db_select('dwsim_flowsheet_proposal');
	$query->fields('dwsim_flowsheet_proposal');
	$query->condition('approval_status', 1);
	$query->condition('is_completed', 0);
	$result = $query->execute();
	if ($result->rowCount() == 0)
	{
		$page_content .= "Work is in progress for the following flowsheets under Flowsheeting Project<hr>";
	} //$result->rowCount() == 0
	else
	{
		$page_content .= "Work is in progress for the following flowsheets under Flowsheeting Project<hr>";
		$page_content .= "<ol>";
		while ($row = $result->fetchObject())
		{
			$page_content .= "<li>";
			$page_content .= $row->project_title;
			$page_content .= "</li>";
		} //$row = $result->fetchObject()
		$page_content .= "</ol>";
	}
	return $page_content;
}
